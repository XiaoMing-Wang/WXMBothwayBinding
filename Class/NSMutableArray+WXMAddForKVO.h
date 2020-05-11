//
//  NSMutableArray+WXMAddForKVO.h
//  ModuleDebugging
//
//  Created by edz on 2019/7/31.
//  Copyright © 2019 wq. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSMutableArray (WXMAddForKVO)

- (void)kvo_setObserver:(id)observer keyPath:(NSString *)keyPath;

/** 添加 */
- (void)kvo_addObject:(id)anObject;
- (void)kvo_addObjectsFromArray:(NSArray *)otherArray;

- (void)kvo_insertObject:(id)anObject atIndex:(NSUInteger)index;

- (void)kvo_removeLastObject;
- (void)kvo_removeAllObjects;
- (void)kvo_removeObject:(id)anObject;
- (void)kvo_removeObjectAtIndex:(NSUInteger)index;

/** 替换 */
- (void)kvo_setArray:(NSArray *)otherArray;
- (void)kvo_replaceArray:(NSArray *)otherArray;

@end

@interface UITextField (WXMAddForKVO)

- (WXMKVOObserveSignal *)wr_textSignal;
- (void)kvo_addTargetForAllEditingEvents;

@end


NS_ASSUME_NONNULL_END
