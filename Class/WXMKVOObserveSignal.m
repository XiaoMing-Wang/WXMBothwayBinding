//
//  WXMKVOBlockTarget.m
//  ModuleDebugging
//
//  Created by edz on 2019/7/26.
//  Copyright © 2019 wq. All rights reserved.
//
#import "WXMKVOObserveSignal.h"
#import "NSObject+WXMAddForKVO.h"
#import "NSMutableArray+WXMAddForKVO.h"

@interface WXMKVOObserveSignal ()
@property (nonatomic, assign) BOOL isEqualValue;    /** 新旧值相同 */
@property (nonatomic, assign) BOOL isManualTrigger; /** 手动触发 */
@property (nonatomic, assign) BOOL isColdSignal;    /** 是否冷信号 */
@property (nonatomic, assign) NSInteger sendCount;  /** 触发次数 */
@property (nonatomic, weak) id oldObject;
@property (nonatomic, weak) NSObject *target;
@property (nonatomic, copy) NSString *keyPath;
@property (nonatomic, strong) NSMutableArray<KVOCallBack> *callbackArray;
@end

@implementation WXMKVOObserveSignal

- (instancetype)initWithTarget:(__weak NSObject *)target keyPath:(NSString *)keyPath {
    self = [self initWeakWithTarget:target keyPath:keyPath];
    
    /** 把WXMKVOObserveSignal绑定到监听对象上target 否则block被释放 */
    if (target && keyPath) [target addSignal:self keyPath:keyPath];
    
    return self;
}

- (instancetype)initWeakWithTarget:(__weak NSObject *)target keyPath:(NSString *)keyPath {
    
    if (target == nil || keyPath == nil) return nil;
    if (self = [super init])  {
        self.sendCount = 0;
        self.target = target;
        self.keyPath = keyPath.copy;
        
        /** self作为kvo的监听者 */
        /** self作为kvo的监听者 */
        /** self作为kvo的监听者 */
        if (target && keyPath) [target addObserverBlockForKeyPath:keyPath signal:self];
    }
    
    WXMPreventCrashBegin
    id object = [target valueForKey:keyPath];
    if ([object isKindOfClass:NSMutableArray.class] && target && object) {
        NSMutableArray *array = (NSMutableArray *) object;
        [array kvo_setObserver:target keyPath:keyPath];
    }
    
    if ([target isKindOfClass:[UITextField class]]) {
        UITextField *textField = (UITextField *) target;
        [textField kvo_addTargetForAllEditingEvents];
    }
    
    WXMPreventCrashEnd
    return self;
}

/** 监听调用 */
- (void)observeValueForKeyPath:(NSString *)keyPath
                      ofObject:(id)object
                        change:(NSDictionary *)change
                       context:(void *)context {
    if (self.callbackArray.count == 0 || !self.callbackArray) return;
    BOOL isPrior = [[change objectForKey:NSKeyValueChangeNotificationIsPriorKey] boolValue];
    if (isPrior) return;
    
    NSKeyValueChange changeKind = [[change objectForKey:NSKeyValueChangeKindKey] integerValue];
    if (changeKind != NSKeyValueChangeSetting) return;
    
    id oldVal = [change objectForKey:NSKeyValueChangeOldKey];
    if (oldVal == [NSNull null]) oldVal = nil;
    
    id newVal = [change objectForKey:NSKeyValueChangeNewKey];
    if (newVal == [NSNull null]) newVal = nil;
    
    WXMPreventCrashBegin
    
    /** 手动触发 */
    self.isManualTrigger = NO;
    
    /** 值是否相同 */
    self.isEqualValue = ([oldVal isEqualValue:newVal]);
    
    /** 调用次数 */
    self.sendCount = self.sendCount + 1;
    [self sendSignal:newVal];
    WXMPreventCrashEnd
}

/** 发出 */
- (void)sendSignal:(id)newVal {
    for (KVOCallBack callback in self.callbackArray) {
        if (callback) callback(newVal);
    }
}

/** 手动触发 */
- (void)manualTriggerSignal:(id)newVal {
    self.isManualTrigger = YES;
    [self sendSignal:newVal];
}

/** 订阅 */
- (void)subscribeNext:(KVOCallBack)callback {
    if (callback == nil) return;
    @synchronized (self) {
        if (self.isColdSignal && self.oldObject) callback(self.oldObject);
        [self.callbackArray addObject:[callback copy]];
    }
}

/** 信号合并 */
- (void)combineSignal:(WXMKVOObserveSignal *)otherSignal {
    @synchronized (self) {
        NSMutableArray *allBackArray = @[].mutableCopy;
        [allBackArray addObjectsFromArray:self.callbackArray];
        [allBackArray addObjectsFromArray:otherSignal.callbackArray];
        self.callbackArray = allBackArray.mutableCopy;
        otherSignal.callbackArray = allBackArray.mutableCopy;
    }
}

/** 信号合并 */
- (WXMKVOObserveSignal *)reCombineSignal:(WXMKVOObserveSignal *)otherSignal {
    WXMPreventCrashBegin
    @synchronized (self) {
        WXMKVOObserveSignal *reCombinesignal = [[WXMKVOObserveSignal alloc] init];
        
        [self subscribeNext:^(id newVal) {
            [reCombinesignal sendSignal:newVal];
        }];
        
        [otherSignal subscribeNext:^(id newVal) {
            [reCombinesignal sendSignal:newVal];
        }];
        return reCombinesignal;
    }
    WXMPreventCrashEnd
}

/** 包装信号 */
- (WXMKVOObserveSignal *)map:(id (^)(id newVal))wrap {
    WXMPreventCrashBegin
    WXMKVOObserveSignal *wrapSignal = [[WXMKVOObserveSignal alloc] init];
    
    [self subscribeNext:^(id newVal) {
        [wrapSignal sendSignal:wrap(newVal)];
    }];
    return wrapSignal;
    WXMPreventCrashEnd
}

/** 过滤 */
- (WXMKVOObserveSignal *)filter:(BOOL (^)(id newVal))wrap {
    WXMPreventCrashBegin
    WXMKVOObserveSignal *filterSignal = [[WXMKVOObserveSignal alloc] init];
    [self subscribeNext:^(id newVal) {
        
        BOOL conversionObj = wrap(newVal);
        if (conversionObj) [filterSignal sendSignal:newVal];
        
    }];
    return filterSignal;
    WXMPreventCrashEnd
}

/** 跳跃 */
- (WXMKVOObserveSignal *)skip:(NSInteger)skipCount {
    WXMPreventCrashBegin
    WXMKVOObserveSignal *skipSignal = [[WXMKVOObserveSignal alloc] init];
    
    __weak typeof(self) weakSelf = self;
    [self subscribeNext:^(id newVal) {
        
        __strong __typeof(weakSelf) strongSelf = weakSelf;
        if (skipCount < strongSelf.sendCount) {
            [skipSignal sendSignal:newVal];
        }
        
    }];
    return skipSignal;
    WXMPreventCrashEnd
}

/** 变化 */
- (WXMKVOObserveSignal *)distinctUntilChanged {
    WXMPreventCrashBegin
    WXMKVOObserveSignal *changeSignal = [[WXMKVOObserveSignal alloc] init];
    
    __weak typeof(self) weakSelf = self;
    [self subscribeNext:^(id newVal) {
        
        __strong __typeof(weakSelf) strongSelf = weakSelf;
        if (strongSelf.isEqualValue == NO) [changeSignal sendSignal:newVal];
        
    }];
    
    return changeSignal;
    WXMPreventCrashEnd
}

/** 只能手动触发 */
- (WXMKVOObserveSignal *)didChangeManual {
    WXMPreventCrashBegin
    WXMKVOObserveSignal *manualSignal = [[WXMKVOObserveSignal alloc] init];
    
    __weak typeof(self) weakSelf = self;
    [self subscribeNext:^(id newVal) {
        
        __strong __typeof(weakSelf) strongSelf = weakSelf;
        if (strongSelf.isManualTrigger) [manualSignal sendSignal:newVal];
        
    }];
    
    return manualSignal;
    WXMPreventCrashEnd
}

/** 冷信号 订阅既发 */
- (WXMKVOObserveSignal *)coldSignal {
    WXMPreventCrashBegin
    WXMKVOObserveSignal *cSignal = [[WXMKVOObserveSignal alloc] init];
    cSignal.isColdSignal = YES;
    cSignal.oldObject = [self.target valueForKey:self.keyPath];
    
    [self subscribeNext:^(id newVal) {
        [cSignal sendSignal:newVal];
    }];
    
    return cSignal;
    WXMPreventCrashEnd
}

- (NSMutableArray<KVOCallBack> *)callbackArray {
    if (!_callbackArray) _callbackArray = @[].mutableCopy;
    return _callbackArray;
}

- (void)dealloc {
    /** NSLog(@"-----------> %@", @"WXMKVOObserveSignal被释放"); */
}

@end
