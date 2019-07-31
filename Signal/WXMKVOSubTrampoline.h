//
//  WXMKVOPutSignal.h
//  ModuleDebugging
//
//  Created by edz on 2019/7/29.
//  Copyright © 2019 wq. All rights reserved.
//

#define WXMPut(TARGET, KEYPATH) \
[[WXMKVOSubTrampoline alloc] initWithTarget:(TARGET)][@wxmkeypath(TARGET, KEYPATH)]

/** 监听 */
#import "WXMHumbleRACMacro.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class WXMKVOObserveSignal;
@interface WXMKVOSubTrampoline : NSObject

- (nullable instancetype)initWithTarget:(nullable id)target;

/** 点语法 */
- (void)setObject:(WXMKVOObserveSignal *)signal forKeyedSubscript:(NSString *)keyPath;

@end

NS_ASSUME_NONNULL_END
