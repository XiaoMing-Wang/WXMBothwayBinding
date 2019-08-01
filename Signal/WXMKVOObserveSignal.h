//
//  WXMKVOBlockTarget.h
//  ModuleDebugging
//
//  Created by edz on 2019/7/26.
//  Copyright © 2019 wq. All rights reserved.
//

#define WXMObserve(TARGET, KEYPATH) \
[[WXMKVOObserveSignal alloc] initWithTarget:(TARGET) keyPath:@wxmkeypath(TARGET, KEYPATH)]

/** 信号 */
#import "WXMHumbleRACMacro.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface WXMKVOObserveSignal : NSObject

- (instancetype)initWithTarget:(__weak NSObject *)target keyPath:(NSString *)keyPath;
- (instancetype)initWeakWithTarget:(__weak NSObject *)target keyPath:(NSString *)keyPath;

/** 订阅 */
- (void)subscribeNext:(KVOCallBack)callback;

/** 包装 */
- (WXMKVOObserveSignal *)map:(id (^)(id newVal))wrap;

/** 过滤 */
- (WXMKVOObserveSignal *)filter:(BOOL (^)(id newVal))wrap;

/** 跳跃 */
- (WXMKVOObserveSignal *)skip:(NSInteger)skipCount;

/** 判断变化 */
- (WXMKVOObserveSignal *)distinctUntilChanged;

/** 合并 */
- (void)combineSignal:(WXMKVOObserveSignal *)otherSignal;

@end

NS_ASSUME_NONNULL_END
