//
//  NSObject+WXMAddForKVO.m
//  ModuleDebugging
//
//  Created by edz on 2019/7/26.
//  Copyright © 2019 wq. All rights reserved.

#import <objc/objc.h>
#import <objc/runtime.h>
#import "NSObject+WXMAddForKVO.h"
#import "WXMKVOObserveSignal.h"
#import "WXMKVOObserveFollower.h"
#import "WXMKVOBindChannel.h"

@implementation NSObject (WXMAddForKVO)
@dynamic signDictionary;
@dynamic subscripDictionary;
@dynamic channelDictionary;

- (void)addObserverBlockForKeyPath:(NSString *)keyPath signal:(NSObject *)signal {
    WXMPreventCrashBegin
    
    if (!keyPath || !signal) return;
    [self addObserver:signal
           forKeyPath:keyPath
              options:NSKeyValueObservingOptionNew | NSKeyValueObservingOptionOld
              context:NULL];
    
    //if ([[UIDevice currentDevice] systemVersion].floatValue < 11.0) {
    //[self managerObserveSignalDealloc];
    //}
    WXMPreventCrashEnd
}

- (void)addSignal:(WXMKVOObserveSignal *)observeSignal keyPath:(NSString *)keyPath {
    WXMPreventCrashBegin
    
    NSMutableDictionary *dic = self.signDictionary;
    NSMutableArray *array = dic[keyPath];
    if (!array) {
        array = [NSMutableArray new];
        dic[keyPath] = array;
    }
    [array addObject:observeSignal];
    
    WXMPreventCrashEnd
}

- (void)addSubscrip:(WXMKVOObserveFollower *)subTrampoline keyPath:(NSString *)keyPath {
    WXMPreventCrashBegin
    
    NSMutableDictionary *dic = self.subscripDictionary;
    NSMutableArray *array = dic[keyPath];
    if (!array) {
        array = [NSMutableArray new];
        dic[keyPath] = array;
    }
    [array addObject:subTrampoline];
    
    WXMPreventCrashEnd
}

- (void)addBindChannel:(WXMKVOBindChannel *)bindChannel keyPath:(NSString *)keyPath {
    WXMPreventCrashBegin
    
    NSMutableDictionary *dic = self.channelDictionary;
    NSMutableArray *array = dic[keyPath];
    if (!array) {
        array = [NSMutableArray new];
        dic[keyPath] = array;
    }
    [array addObject:bindChannel];
    
    WXMPreventCrashEnd
}

- (void)removeObserverBlocks {
    WXMPreventCrashBegin
    
    NSMutableDictionary *targets = objc_getAssociatedObject(self, @selector(signDictionary));
    if (targets.allKeys.count == 0 || !targets) return;
    [targets enumerateKeysAndObjectsUsingBlock: ^(NSString *key, NSArray *array, BOOL *stop) {
        [array enumerateObjectsUsingBlock: ^(id obj, NSUInteger idx, BOOL *stop) {
            [self removeObserver:obj forKeyPath:key];
        }];
    }];
    [targets removeAllObjects];
    
    WXMPreventCrashEnd
}

- (void)removeObserverForKeyPath:(NSString *)keyPath {
    WXMPreventCrashBegin
    
    if (!keyPath) return;
    NSMutableDictionary *targets = objc_getAssociatedObject(self, @selector(signDictionary));
    if (targets.allKeys.count == 0 || !targets) return;
    NSMutableArray *array = [[targets objectForKey:keyPath] mutableCopy];
    [array enumerateObjectsUsingBlock: ^(id obj, NSUInteger idx, BOOL *stop) {
        [self removeObserver:obj forKeyPath:keyPath];
    }];
    [targets removeObjectForKey:keyPath];
    
    WXMPreventCrashEnd
    
}

/** 手动触发信号 */
+ (void)manualTriggerObserveSignal:(NSObject *)object keyPath:(NSString *)keyPath {
    WXMPreventCrashBegin
    
    NSMutableDictionary *dic = object.signDictionary;
    NSMutableArray <WXMKVOObserveSignal *>*array = dic[keyPath];
    id newVal = [object valueForKey:keyPath];
    [array enumerateObjectsUsingBlock:^(WXMKVOObserveSignal *obj, NSUInteger idx, BOOL *stop) {
        [obj manualTriggerSignal:newVal];
    }];
    
    WXMPreventCrashEnd
}

/** 替换dealloc提前释放掉servicer */
- (void)managerObserveSignalDealloc {
    WXMPreventCrashBegin
    
    __block SEL serviceDeallocSEL = NSSelectorFromString(@"observeSignalDealloc");
    if ([self respondsToSelector:serviceDeallocSEL]) return;
    if (!self) return;
    if (!serviceDeallocSEL) return;
    
    id serviceDealloc = ^(__unsafe_unretained id dependInstance) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
#pragma clang diagnostic ignored "-Wundeclared-selector"
        if ([dependInstance respondsToSelector:serviceDeallocSEL] && dependInstance) {
            [dependInstance removeObserverBlocks];
            [dependInstance performSelector:serviceDeallocSEL];
        }
#pragma clang diagnostic pop
    };
    
    Class class = [self class];
    class_addMethod(class, serviceDeallocSEL, imp_implementationWithBlock(serviceDealloc), "v@:@");
    Method deallocMethod = class_getInstanceMethod(class, NSSelectorFromString(@"dealloc"));
    Method serviceMethod = class_getInstanceMethod(class, serviceDeallocSEL);
    method_exchangeImplementations(deallocMethod, serviceMethod);
    
    WXMPreventCrashEnd
}

#pragma mark Lazy

- (NSMutableDictionary<NSString*, NSMutableArray*> *)signDictionary {
    NSMutableDictionary *dictionary = objc_getAssociatedObject(self, _cmd);
    if (!dictionary) {
        dictionary = @{}.mutableCopy;
        objc_setAssociatedObject(self, _cmd, dictionary, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    }
    return dictionary;
}

- (NSMutableDictionary<NSString*, NSMutableArray*> *)subscripDictionary {
    NSMutableDictionary *dictionary = objc_getAssociatedObject(self, _cmd);
    if (!dictionary) {
        dictionary = @{}.mutableCopy;
        objc_setAssociatedObject(self, _cmd, dictionary, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    }
    return dictionary;
}

- (NSMutableDictionary<NSString*, NSMutableArray*> *)channelDictionary {
    NSMutableDictionary *dictionary = objc_getAssociatedObject(self, _cmd);
    if (!dictionary) {
        dictionary = @{}.mutableCopy;
        objc_setAssociatedObject(self, _cmd, dictionary, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    }
    return dictionary;
}

- (void)setNilValueForKey:(NSString *)key {}
- (void)setValue:(id)value forUndefinedKey:(NSString *)key {}
- (BOOL)isEqualValue:(id)object {
    if (self == object) return YES;
    if ([self isKindOfClass:NSString.class] &&
        [object isKindOfClass:NSString.class]) {
        NSString *aString = (NSString *)self;
        NSString *bString = (NSString *)object;
        return [aString isEqualToString:bString];
    }
    
    if ([self isKindOfClass:NSNumber.class] &&
        [object isKindOfClass:NSNumber.class]) {
        NSNumber *aNumber = (NSNumber *)self;
        NSNumber *bNumber= (NSNumber *)object;
        return (aNumber.floatValue == bNumber.floatValue);
    }
    
    return NO;
}

@end
