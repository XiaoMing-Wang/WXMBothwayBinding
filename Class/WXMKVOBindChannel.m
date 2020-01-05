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
    id target = self.target;
    NSString *keyPath = self.keyPath;
    
    /** signal不绑定在target上 由BindChannel强持有signal */
    _followingTerminal = [[WXMKVOObserveSignal alloc] initWeakWithTarget:target keyPath:keyPath];
    [_followingTerminal subscribeNext:self.subscribeBlock];
}

- (KVOCallBack)subscribeBlock {
    
    __weak typeof(self) self_weak = self;
    return ^(id newVal) {
        WXMPreventCrashBegin
        
        __strong __typeof(self_weak) self = self_weak;
        id target = self.target;
        NSString *keyPath = self.keyPath;
        if (![keyPath hasPrefix:@"_"]) {
            keyPath = [@"_" stringByAppendingString:keyPath];
        }
        
        /** 修改_不会触发kvo */
        if (!target) return;
        const char *ivarKey = [keyPath UTF8String];
        Ivar ivar = class_getInstanceVariable([target class], ivarKey);
        if (target && ivar && newVal) {
            @synchronized (target) {
                object_setIvar(target, ivar, newVal);
            }
        }
        
        WXMPreventCrashEnd
    };
}

- (WXMKVOObserveSignal *)objectForKeyedSubscript:(NSString *)key {
    return self.followingTerminal;
}

- (void)setObject:(WXMKVOObserveSignal *)otherTerminal forKeyedSubscript:(NSString *)key {
    WXMKVOObserveSignal *selfSignal = [self objectForKeyedSubscript:key];
    WXMKVOObserveSignal *otherSignal = otherTerminal;
    [selfSignal combineSignal:otherSignal];
}

@end
