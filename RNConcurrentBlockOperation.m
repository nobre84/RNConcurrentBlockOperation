//
// RNConcurrentBlockOperation.h
//
// Copyright (c) 2013 Rafael Nobre
//
// https://github.com/nobre84/RNConcurrentBlockOperation
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#import "RNConcurrentBlockOperation.h"

@interface RNConcurrentBlockOperation()

@property (nonatomic, copy) RNOperationBLock operationBlock;

@end

@implementation RNConcurrentBlockOperation {
    BOOL _isFinished, _isExecuting;
}

+(instancetype)operationWithBlock:(RNOperationBLock)operationBlock {
    id operation = [[self alloc]initWithBlock:operationBlock];
    return operation;
}

-(instancetype)initWithBlock:(RNOperationBLock)operationBlock {
    if (self = [super init]) {
        _isExecuting = NO;
        _isFinished = NO;
        self.operationBlock = operationBlock;
    }
    return self;
}

-(BOOL)isConcurrent {
    return YES;
}

-(void)start {
    @autoreleasepool {
        //some RunLoop based asynchronous work must be started from the main thread so we ensure we start there.
        if (![NSThread isMainThread]) {
            [self performSelectorOnMainThread:@selector(start) withObject:nil waitUntilDone:NO];
        }
        
        //if the operation has been cancelled before starting, finish right away.
        if ([self isCancelled]) {
            [self finish];
            return;
        }
        
        //start execution
        [self willChangeValueForKey:@"isExecuting"];
        _isExecuting = YES;
        [self didChangeValueForKey:@"isExecuting"];
        
        //call the operation block and finish the operation when it signals completion
        self.operationBlock(^{
            [self finish];
        });
    }
}

-(BOOL)isFinished {
    return _isFinished;
}

-(BOOL)isExecuting {
    return _isExecuting;
}

-(void)finish {
    [self willChangeValueForKey:@"isExecuting"];
    [self willChangeValueForKey:@"isFinished"];
    
    _isExecuting = NO;
    _isFinished = YES;
    
    [self didChangeValueForKey:@"isExecuting"];
    [self didChangeValueForKey:@"isFinished"];
}

@end
