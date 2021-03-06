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
    
    __weak typeof(self) weakSelf = self;
    return ^(id newVal) {
        WXMPreventCrashBegin
        
        __strong __typeof(weakSelf) strongSelf = weakSelf;
        id target = strongSelf.target;
        NSString *keyPath = strongSelf.keyPath;
        id value = [target valueForKey:keyPath];
        if ([value isEqualValue:newVal] || (newVal == nil && value == nil)) return;
        if (![keyPath hasPrefix:@"_"]) keyPath = [@"_" stringByAppendingString:keyPath];
        if (!target || !keyPath) return;
        
        /** 修改带_不会触发kvo 但是系统的某些变量有时获取不到 比如textFile的text */
        /** 修改带_不会触发kvo 但是系统的某些变量有时获取不到 比如textFile的text */
        /** 修改带_不会触发kvo 但是系统的某些变量有时获取不到 比如textFile的text */
        const char *ivarKey = [keyPath UTF8String];
        Ivar ivar = class_getInstanceVariable([target class], ivarKey);
        if (target && ivar && newVal) {
            
            
            @synchronized (target) {
                object_setIvar(target, ivar, newVal);
            }
            
            /** UITextField的设置text设置不会调用kvo功能 需要自己设置 UITextField和NSArray需要特殊处理 */
            /** UITextField的设置text设置不会调用kvo功能 需要自己设置 UITextField和NSArray需要特殊处理 */
            /** UITextField的设置text设置不会调用kvo功能 需要自己设置 UITextField和NSArray需要特殊处理 */
        } else if ([target isKindOfClass:UITextField.class] && [keyPath isEqualToString:@"_text"]) {
            
            @synchronized (target) {
                UITextField *textField = (UITextField *)target;
                textField.text = newVal;
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
