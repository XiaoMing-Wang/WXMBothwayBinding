//
//  WXMKVOChannel.h
//  ModuleDebugging
//
//  Created by edz on 2019/7/29.
//  Copyright © 2019 wq. All rights reserved.
//
#define WRBindChannel(TARGET, KEYPATH) \
\
[[WXMKVOBindChannel alloc] initWithTarget:(TARGET) keyPath:@wxmkeypath(TARGET, KEYPATH)] \
[@keypath(WXMKVOBindChannel.new, followingTerminal)]

/** 双向绑定 */
#import "WXMHumbleRACMacro.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class WXMKVOObserveSignal;
@interface WXMKVOBindChannel : NSObject
@property (nonatomic, strong) WXMKVOObserveSignal *followingTerminal;

- (instancetype)initWithTarget:(__weak NSObject *)target keyPath:(NSString *)keyPath;

/** 点语法 */
- (WXMKVOObserveSignal *)objectForKeyedSubscript:(NSString *)key;
- (void)setObject:(WXMKVOObserveSignal *)otherTerminal forKeyedSubscript:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
