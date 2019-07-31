//
//  WXMKVOChannel.m
//  ModuleDebugging
//
//  Created by edz on 2019/7/29.
//  Copyright © 2019 wq. All rights reserved.
//
#import <objc/runtime.h>
#import "WXMKVOBindChannel.h"
#import "WXMKVOObserveSignal.h"
#import "NSObject+WXMAddForKVO.h"
#import "NSMutableArray+WXMAddForKVO.h"

@interface WXMKVOBindChannel ()
@property (nonatomic, weak) NSObject *target;
@property (nonatomic, copy) NSString *keyPath;
@end

@implementation WXMKVOBindChannel
@synthesize followingTerminal = _followingTerminal;

- (instancetype)initWithTarget:(__weak NSObject *)target keyPath:(NSString *)keyPath {
    if (!target || !keyPath) return nil;
    if (self = [super init]) {
        self.target = target;
        self.keyPath = keyPath;
        [self.target addBindChannel:self keyPath:keyPath];
        [self createFollowingTerminal];
    }
    return self;
}

- (void)createFollowingTerminal {
    __weak id target = self.target;
    NSString *keyPath = self.keyPath;
    _followingTerminal = [[WXMKVOObserveSignal alloc] initWeakWithTarget:target keyPath:keyPath];
    [_followingTerminal subscribeNext:self.subscribeBlock];
}

- (KVOCallBack)subscribeBlock {
    WXMPreventCrashBegin
    
    __weak typeof(self) weakSelf = self;
    return ^(id newVal) {
        __strong __typeof(weakSelf) self = weakSelf;
        
        id target = self.target;
        NSString *keyPath = self.keyPath;
        if (![keyPath hasPrefix:@"_"]) keyPath = [@"_" stringByAppendingString:keyPath];
        
        const char *ivarKey = [keyPath UTF8String];
        Ivar ivar = class_getInstanceVariable([target class], ivarKey);
        if (target && ivar && newVal) {
            @synchronized (target) {
                object_setIvar(target, ivar, newVal);
            }
        }
    };
    
    WXMPreventCrashEnd
}

- (WXMKVOObserveSignal *)objectForKeyedSubscript:(NSString *)key {
    return self.followingTerminal;
}

- (void)setObject:(WXMKVOObserveSignal *)otherTerminal forKeyedSubscript:(NSString *)key {
    WXMKVOObserveSignal *selfSignal = [self objectForKeyedSubscript:key];
    WXMKVOObserveSignal *otherSignal = otherTerminal;
    [selfSignal combineSignal:otherSignal];
}

- (void)dealloc {
    /** NSLog(@"%@ 释放", NSStringFromClass(self.class)); */
}
@end
