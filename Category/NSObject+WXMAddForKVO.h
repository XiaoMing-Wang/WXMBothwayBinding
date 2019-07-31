//
//  NSObject+WXMAddForKVO.h
//  ModuleDebugging
//
//  Created by edz on 2019/7/26.
//  Copyright © 2019 wq. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class WXMKVOObserveSignal;
@class WXMKVOSubTrampoline;
@class WXMKVOSelectorExecutor;
@class WXMKVOBindChannel;
@interface NSObject (WXMAddForKVO)

/** 存放信号 */
@property (nonatomic, strong) NSMutableDictionary<NSString*, NSMutableArray*> *signDictionary;
@property (nonatomic, strong) NSMutableDictionary<NSString*, NSMutableArray*> *subscripDictionary;
@property (nonatomic, strong) NSMutableDictionary<NSString*, NSMutableArray*> *channelDictionary;
@property (nonatomic, strong) NSMutableDictionary<NSString*, NSMutableArray*> *selectorDictionary;

- (void)addSignal:(WXMKVOObserveSignal *)observeSignal keyPath:(NSString *)keyPath;
- (void)addSubscrip:(WXMKVOSubTrampoline *)subTrampoline keyPath:(NSString *)keyPath;
- (void)addSelector:(WXMKVOSelectorExecutor *)selector keyPath:(NSString *)keyPath;
- (void)addBindChannel:(WXMKVOBindChannel *)bindChannel keyPath:(NSString *)keyPath;

/** 信号作为kvo响应者 */
- (void)addObserverBlockForKeyPath:(NSString *)keyPath signal:(NSObject *)signal;

/** 删除keyPath */
- (void)removeObserverBlocksForKeyPath:(NSString*)keyPath;

/** 删除所有 */
- (void)removeObserverBlocks;

@end

NS_ASSUME_NONNULL_END
