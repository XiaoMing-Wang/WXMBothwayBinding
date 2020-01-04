//
//  NSObject+WXMAddForKVO.h
//  ModuleDebugging
//
//  Created by edz on 2019/7/26.
//  Copyright © 2019 wq. All rights reserved.
//
#define WRKVOManualTrigger(TARGET, KEYPATH) \
[NSObject manualTriggerObserveSignal:(TARGET) keyPath:@wxmkeypath(TARGET, KEYPATH)];

#define WRDeleteObserverForKeyPath(TARGET, KEYPATH) \
[TARGET removeObserverForKeyPath:@wxmkeypath(TARGET, KEYPATH)];

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class WXMKVOObserveSignal;
@class WXMKVOObserveFollower;
@class WXMKVOSelectorExecutor;
@class WXMKVOBindChannel;
@interface NSObject (WXMAddForKVO)

/** 存放信号 */
@property (nonatomic, strong) NSMutableDictionary<NSString*, NSMutableArray*> *signDictionary;
@property (nonatomic, strong) NSMutableDictionary<NSString*, NSMutableArray*> *subscripDictionary;
@property (nonatomic, strong) NSMutableDictionary<NSString*, NSMutableArray*> *channelDictionary;

/** 绑定信号 */
- (void)addSignal:(WXMKVOObserveSignal *)observeSignal keyPath:(NSString *)keyPath;

/** 绑定follower */
- (void)addSubscrip:(WXMKVOObserveFollower *)subTrampoline keyPath:(NSString *)keyPath;

/** 绑定双向通道 */
- (void)addBindChannel:(WXMKVOBindChannel *)bindChannel keyPath:(NSString *)keyPath;

/** 信号作为kvo响应者 */
- (void)addObserverBlockForKeyPath:(NSString *)keyPath signal:(NSObject *)signal;

/** 删除所有 */
- (void)removeObserverBlocks;
- (void)removeObserverForKeyPath:(NSString *)keyPath;

/** 判断对象 */
- (BOOL)isEqualValue:(id)object;

/** 手动触发信号 */
+ (void)manualTriggerObserveSignal:(NSObject *)object keyPath:(NSString *)keyPath;

/** 获取所有属性 */
+ (NSArray *)wc_getFropertys;

@end

NS_ASSUME_NONNULL_END