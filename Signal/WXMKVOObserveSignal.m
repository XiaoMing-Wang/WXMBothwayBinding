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
@property (nonatomic, weak) NSObject *target;
@property (nonatomic, copy) NSString *keyPath;
@property (nonatomic, strong) NSMutableArray *callbackArray;
@end

@implementation WXMKVOObserveSignal

/** 监听调用 */
- (void)observeValueForKeyPath:(NSString *)keyPath
                      ofObject:(id)object
                        change:(NSDictionary *)change
                       context:(void *)context {
    
    if (self.callbackArray.count == 0) return;
    BOOL isPrior = [[change objectForKey:NSKeyValueChangeNotificationIsPriorKey] boolValue];
    if (isPrior) return;
    
    NSKeyValueChange changeKind = [[change objectForKey:NSKeyValueChangeKindKey] integerValue];
    if (changeKind != NSKeyValueChangeSetting) return;
    
    id oldVal = [change objectForKey:NSKeyValueChangeOldKey];
    if (oldVal == [NSNull null]) oldVal = nil;
    
    id newVal = [change objectForKey:NSKeyValueChangeNewKey];
    if (newVal == [NSNull null]) newVal = nil;
    
    for (KVOCallBack callback in self.callbackArray) {
        if (callback) callback(newVal);
    }
}

- (instancetype)initWithTarget:(__weak NSObject *)target keyPath:(NSString *)keyPath {
    self = [self initWeakWithTarget:target keyPath:keyPath];
    if (target && keyPath) [target addSignal:self keyPath:keyPath];
    
    return self;
}

- (instancetype)initWeakWithTarget:(__weak NSObject *)target keyPath:(NSString *)keyPath {
    if (target == nil || keyPath == nil) return nil;
    if (self = [super init])  {
        self.target = target;
        self.keyPath = keyPath.copy;
        if (target && keyPath) [target addObserverBlockForKeyPath:keyPath signal:self];
    }
    
    WXMPreventCrashBegin
    id object = [target valueForKey:keyPath];
    if ([object isKindOfClass:NSMutableArray.class] && target && object) {
        NSMutableArray *array = (NSMutableArray *) object;
        [array kvo_setObserver:target keyPath:keyPath];
    }
    WXMPreventCrashEnd
    
    return self;
}

/** 订阅 */
- (void)subscribeNext:(KVOCallBack)callback {
    if (callback == nil) return;
    @synchronized (self) {
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
        if (otherSignal) otherSignal.callbackArray = allBackArray.mutableCopy;
    }
}

- (NSMutableArray *)callbackArray {
    if (!_callbackArray) _callbackArray = @[].mutableCopy;
    return _callbackArray;
}

- (void)dealloc {
    /** NSLog(@"%@ 释放", NSStringFromClass(self.class)); */
}
@end
