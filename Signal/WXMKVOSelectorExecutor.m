//
//  WXMKVOOrderExecutor.m
//  ModuleDebugging
//
//  Created by edz on 2019/7/31.
//  Copyright © 2019 wq. All rights reserved.
//

#import "WXMKVOSelectorExecutor.h"
#import "NSObject+WXMAddForKVO.h"
#import "WXMKVOObserveSignal.h"

@interface WXMKVOSelectorExecutor ()
@property (nonatomic, weak) NSObject *target;
@property (nonatomic, copy) NSString *selector;
@end
@implementation WXMKVOSelectorExecutor

- (instancetype)initWithTarget:(__weak NSObject *)target selector:(NSString *)selector {
    if (!target || !selector) return nil;
    if (self = [super init]) {
        self.target = target;
        self.selector = [selector copy];
    }
    return self;
}

/** 点语法 */
- (void)setObject:(WXMKVOObserveSignal *)signal forKeyedSubscript:(NSString *)keyPath {
    WXMPreventCrashBegin
    
    /** A对象强引用 WXMKVOSubscriptingTrampoline 否则subscribeBlock被释放了 */
    if (self.target) [self.target addSelector:self keyPath:keyPath];
    
    /** 订阅信号 B的信号A也订阅一次 B有变动就会调起A的block */
    if (signal && keyPath && self.target) [signal subscribeNext:self.subscribeBlock];
    
    WXMPreventCrashEnd
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
#pragma clang diagnostic ignored "-Wundeclared-selector"

/** callback */
- (KVOCallBack)subscribeBlock {
    WXMPreventCrashBegin
    
    __weak typeof(self) weakSelf = self;
    return ^(id newVal) {
        
        __strong __typeof(weakSelf) strongSelf = weakSelf;
        id target = strongSelf.target;
        SEL selector = NSSelectorFromString(strongSelf.selector);
        if (target && [target respondsToSelector:selector]) {
            [target performSelector:selector];
        }
    };
    
    WXMPreventCrashEnd
}
#pragma clang diagnostic pop

@end
