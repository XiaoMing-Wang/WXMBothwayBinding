//
//  NSMutableArray+WXMAddForKVO.m
//  ModuleDebugging
//
//  Created by edz on 2019/7/31.
//  Copyright © 2019 wq. All rights reserved.
//
#import <objc/runtime.h>
#import "NSMutableArray+WXMAddForKVO.h"


static char kvo_observerKey;
static char kvo_propertyKey;
@implementation NSMutableArray (WXMAddForKVO)

- (void)kvo_setObserver:(id)observer keyPath:(NSString *)keyPath {
    @try {
        NSString *proper = keyPath;
        objc_setAssociatedObject(self, &kvo_observerKey, observer, OBJC_ASSOCIATION_ASSIGN);
        objc_setAssociatedObject(self, &kvo_propertyKey, proper, OBJC_ASSOCIATION_COPY_NONATOMIC);
    } @catch (NSException *exception) {} @finally {};
}

- (void)kvo_addObject:(id)anObject {
    if (!anObject) return;
    [self kvo_listeningObserver:^{
        [self addObject:anObject];
    }];
}

- (void)kvo_addObjectsFromArray:(NSArray *)otherArray {
    if (!otherArray.count) return;
    [self kvo_listeningObserver:^{
        [self addObjectsFromArray:otherArray];
    }];
}

- (void)kvo_removeLastObject {
    [self kvo_listeningObserver:^{
        [self removeLastObject];
    }];
}

- (void)kvo_removeAllObjects {
    [self kvo_listeningObserver:^{
        [self removeAllObjects];
    }];
}

- (void)kvo_removeObjectAtIndex:(NSUInteger)index {
    [self kvo_listeningObserver:^{
        [self removeObjectAtIndex:index];
    }];
}

- (void)kvo_replaceObjectAtIndex:(NSUInteger)index withObject:(id)anObject {
    [self kvo_listeningObserver:^{
        [self replaceObjectAtIndex:index withObject:anObject];
    }];
}

- (void)kvo_setArray:(NSArray *)otherArray {
    [self kvo_listeningObserver:^{
        [self removeAllObjects];
        [self addObjectsFromArray:otherArray];
    }];
}

- (void)kvo_replaceArray:(NSArray *)otherArray {
    [self kvo_listeningObserver:^{
        [self removeAllObjects];
        [self addObjectsFromArray:otherArray];
    }];
}

- (void)kvo_listeningObserver:(void(^)(void))result {
    id observer = objc_getAssociatedObject(self, &kvo_observerKey);
    NSString *proper = objc_getAssociatedObject(self, &kvo_propertyKey);
    if (!observer || !proper) {
        if (result) result();
        return;
    }
    
    [observer willChangeValueForKey:proper];
    if (result) result();
    [observer didChangeValueForKey:proper];
}

@end
