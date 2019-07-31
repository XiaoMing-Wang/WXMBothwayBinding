//
//  WXMKVOPutSignal.m
//  ModuleDebugging
//
//  Created by edz on 2019/7/29.
//  Copyright © 2019 wq. All rights reserved.
//
#import "WXMKVOSubTrampoline.h"
#import "WXMKVOObserveSignal.h"
#import "NSObject+WXMAddForKVO.h"

@interface WXMKVOSubTrampoline ()
@property (nonatomic, weak) NSObject *target;
@property (nonatomic, copy) NSString *keyPath;
@end
@implementation WXMKVOSubTrampoline

- (nullable instancetype)initWithTarget:(nullable id)target {
    if (!target) return nil;
    if (self = [super init]) self.target = target;
    return self;
}

- (void)setObject:(WXMKVOObserveSignal *)signal forKeyedSubscript:(NSString *)keyPath {
    WXMPreventCrashBegin
    
    self.keyPath = [keyPath copy];
    
    /** A对象强引用 WXMKVOSubscriptingTrampoline 否则subscribeBlock被释放了 */
    if (self.target) [self.target addSubscrip:self keyPath:keyPath];
    
    /** 订阅信号 B的信号A也订阅一次 B有变动就会调起A的block */
    if (signal && keyPath && self.target) [signal subscribeNext:self.subscribeBlock];
    
    WXMPreventCrashEnd
}

/** callback */
- (KVOCallBack)subscribeBlock {
    WXMPreventCrashBegin
    
    __weak typeof(self) weakSelf = self;
    return ^(id newVal) {
        __strong __typeof(weakSelf) self = weakSelf;
        
        id target = self.target;
        NSString *keyPath = self.keyPath;
        if (target && keyPath && newVal) [target setValue:newVal forKey:keyPath];
    };
    
    WXMPreventCrashEnd
}

@end
