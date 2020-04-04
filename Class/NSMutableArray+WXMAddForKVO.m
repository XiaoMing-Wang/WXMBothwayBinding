//
//  NSMutableArray+WXMAddForKVO.m
//  ModuleDebugging
//
//  Created by edz on 2019/7/31.
//  Copyright © 2019 wq. All rights reserved.
//
#import <objc/runtime.h>
#import "NSMutableArray+WXMAddForKVO.h"
#import "WXMHumbleRACMacro.h"

static char kvo_observerKey;
static char kvo_propertyKey;
@implementation NSMutableArray (WXMAddForKVO)

- (void)kvo_setObserver:(id)observer keyPath:(NSString *)keyPath {
    WXMPreventCrashBegin
    NSString *proper = keyPath;
    objc_setAssociatedObject(self, &kvo_observerKey, observer, OBJC_ASSOCIATION_ASSIGN);
    objc_setAssociatedObject(self, &kvo_propertyKey, proper, OBJC_ASSOCIATION_COPY_NONATOMIC);
    WXMPreventCrashEnd
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

- (void)kvo_insertObject:(id)anObject atIndex:(NSUInteger)index {
    if (self.count < index) return;
    [self kvo_listeningObserver:^{
        [self insertObject:anObject atIndex:index];
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

- (void)kvo_removeObject:(id)anObject {
    if (!anObject) return;
    [self kvo_listeningObserver:^{
        [self removeObject:anObject];
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
    WXMPreventCrashBegin
    
    id observer = objc_getAssociatedObject(self, &kvo_observerKey);
    NSString *proper = objc_getAssociatedObject(self, &kvo_propertyKey);
    if (!observer || !proper) {
        if (result) result();
        return;
    }
    
    [observer willChangeValueForKey:proper];
    if (result) result();
    [observer didChangeValueForKey:proper];
    WXMPreventCrashEnd
}

@end


@implementation UITextField (WXMAddForKVO)

- (void)kvo_addTargetForAllEditingEvents {
    [self addTarget:self
             action:@selector(kvo_textFieldDidChange)
   forControlEvents:UIControlEventAllEditingEvents];
}

- (void)kvo_textFieldDidChange {
    [self willChangeValueForKey:@wxmkeypath(self, text)];
    [self didChangeValueForKey:@wxmkeypath(self, text)];
}


@end
