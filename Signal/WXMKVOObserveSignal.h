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

/** 强引用 */
- (instancetype)initWithTarget:(__weak NSObject *)target keyPath:(NSString *)keyPath;

/** 弱引用 */
- (instancetype)initWeakWithTarget:(__weak NSObject *)target keyPath:(NSString *)keyPath;

/** 订阅 */
- (void)subscribeNext:(KVOCallBack)callback;

/** 包装 */
- (WXMKVOObserveSignal *)map:(id (^)(id newVal))wrap;

/** 过滤 */
- (WXMKVOObserveSignal *)filter:(BOOL (^)(id newVal))wrap;

/** 跳跃 */
- (WXMKVOObserveSignal *)skip:(NSInteger)skipCount;

/** 变化 */
- (WXMKVOObserveSignal *)distinctUntilChanged;

/** 只能手动触发 */
- (WXMKVOObserveSignal *)manualTrigger;

/** 冷信号 订阅既发 */
- (WXMKVOObserveSignal *)coldSignal;

/** 合并信号 */
- (void)combineSignal:(WXMKVOObserveSignal *)otherSignal;

/** 触发 */
- (void)manualTriggerSignal:(id)newVal;

@end

NS_ASSUME_NONNULL_END
