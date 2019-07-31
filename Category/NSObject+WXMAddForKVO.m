//
//  NSObject+WXMAddForKVO.m
//  ModuleDebugging
//
//  Created by edz on 2019/7/26.
//  Copyright © 2019 wq. All rights reserved.
//
/** key1-@[sign1, sign2] */
/** key2-@[sign1, sign2] */
#import <objc/objc.h>
#import <objc/runtime.h>
#import "NSObject+WXMAddForKVO.h"
#import "WXMKVOObserveSignal.h"
#import "WXMKVOSubTrampoline.h"

@implementation NSObject (WXMAddForKVO)
@dynamic signDictionary;
@dynamic subscripDictionary;
@dynamic selectorDictionary;
@dynamic channelDictionary;

+ (void)load {
    Method method1 = class_getInstanceMethod(self, NSSelectorFromString(@"dealloc"));
    Method method2 = class_getInstanceMethod(self, @selector(__kvoTargetDealloc));
    method_exchangeImplementations(method1, method2);
}

- (void)addObserverBlockForKeyPath:(NSString *)keyPath signal:(NSObject *)signal {
    WXMPreventCrashBegin
    
    if (!keyPath || !signal) return;
    [self addObserver:signal
           forKeyPath:keyPath
              options:NSKeyValueObservingOptionNew
              context:NULL];
    
    WXMPreventCrashEnd
}

- (void)removeObserverBlocksForKeyPath:(NSString*)keyPath {
    WXMPreventCrashBegin
    
    if (!keyPath) return;
    NSMutableDictionary *dictionary = self.signDictionary;
    NSMutableArray *array = dictionary[keyPath];
    [array enumerateObjectsUsingBlock: ^(id obj, NSUInteger idx, BOOL *stop) {
        [self removeObserver:obj forKeyPath:keyPath];
    }];
    [dictionary removeObjectForKey:keyPath];
    
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

- (void)addSignal:(WXMKVOObserveSignal *)observeSignal keyPath:(NSString *)keyPath; {
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

- (void)addSubscrip:(WXMKVOSubTrampoline *)subTrampoline keyPath:(NSString *)keyPath {
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

- (void)addSelector:(WXMKVOSelectorExecutor *)selector keyPath:(NSString *)keyPath {
    WXMPreventCrashBegin
    
    NSMutableDictionary *dic = self.selectorDictionary;
    NSMutableArray *array = dic[keyPath];
    if (!array) {
        array = [NSMutableArray new];
        dic[keyPath] = array;
    }
    [array addObject:selector];
    
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

- (NSMutableDictionary<NSString*, NSMutableArray*> *)selectorDictionary {
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

- (void)__kvoTargetDealloc {
    [self removeObserverBlocks];
    [self __kvoTargetDealloc];
}

@end
