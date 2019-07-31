//
//  WXMKVOOrderExecutor.h
//  ModuleDebugging
//
//  Created by edz on 2019/7/31.
//  Copyright © 2019 wq. All rights reserved.
//

#define WXMSelector(TARGET, Selector) \
[[WXMKVOSelectorExecutor alloc] initWithTarget:(TARGET) selector:@wxmkeypath(TARGET, Selector)]\
[@wxmkeypath(TARGET, Selector)]

/** 监听函数调用 */
#import "WXMHumbleRACMacro.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class WXMKVOObserveSignal;
@interface WXMKVOSelectorExecutor : NSObject

- (instancetype)initWithTarget:(__weak NSObject *)target selector:(NSString *)selector;

/** 点语法 */
- (void)setObject:(WXMKVOObserveSignal *)signal forKeyedSubscript:(NSString *)keyPath;

@end

NS_ASSUME_NONNULL_END
