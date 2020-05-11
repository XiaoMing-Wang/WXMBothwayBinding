//
//  WXMKVOPutSignal.m
//  ModuleDebugging
//
//  Created by edz on 2019/7/29.
//  Copyright © 2019 wq. All rights reserved.
//
#import "WXMKVOObserveFollower.h"
#import "WXMKVOObserveSignal.h"
#import "NSObject+WXMAddForKVO.h"

@interface WXMKVOObserveFollower ()
@property (nonatomic, weak) NSObject *target;
@property (nonatomic, copy) NSString *keyPath;
@end
@implementation WXMKVOObserveFollower

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
    if (signal && keyPath && self.target){
        [signal subscribeNext:self.subscribeBlock];
    }
    
    WXMPreventCrashEnd
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
#pragma clang diagnostic ignored "-Wundeclared-selector"

/** callback */
- (KVOCallBack)subscribeBlock {
       
    __weak typeof(self) weakSelf = self;
    return ^(id newVal) {
        WXMPreventCrashBegin
        
        __strong __typeof(weakSelf) strongSelf = weakSelf;
        id target = strongSelf.target;
        NSString *keyPath = strongSelf.keyPath;
        id value = [target valueForKey:keyPath];
        if ([value isEqualValue:newVal] || (newVal == nil && value == nil)) return;
             
        if (target && keyPath && newVal) {
            
            /** setValue不存在的属性设置不会崩溃 */
            /** setValue不存在的属性设置不会崩溃 */
            /** setValue不存在的属性设置不会崩溃 */
            [target setValue:newVal forKey:keyPath];
            
            /** 如果这个是函数的话 */
            /** 如果这个是函数的话 */
            /** 如果这个是函数的话 */
            SEL selector = NSSelectorFromString(keyPath);
            if ([target respondsToSelector:selector] && selector) {
                [target performSelector:selector];
            }
        }
        
        WXMPreventCrashEnd
    };
}

#pragma clang diagnostic pop

@end
