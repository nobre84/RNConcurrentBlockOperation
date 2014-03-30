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


/**
 
 RNConcurrentBlockOperation
 ==========================
 
 RNConcurrentBlockOperation is a simple NSOperation subclass, similar to NSBlockOperation. It allows a block of work that is potentially asynchrounous to be submited into a NSOperationQueue for parallel execution.
 
 
 Sample usage:
 
 NSOperationQueue *queue = [NSOperationQueue new];
 queue.maxConcurrentOperations = 5;
 RNConcurrentBlockOperation *asyncOperation = [RNConcurrentBlockOperation operationWithBlock:^(RNCompletionBlock completion) {
 //Some async operation
 //... ... ...
 //Async operation completed
 completion();
 }];
 [queue addOperation:asyncOperation];
 
 
 */

#import <Foundation/Foundation.h>
@class RNConcurrentBlockOperation;

typedef void (^RNCompletionBlock) (NSDictionary *userInfo);
typedef void (^RNCancelationBlock) (NSDictionary *userInfo);
typedef void (^RNOperationBlock) (RNCompletionBlock completion);
typedef void (^RNCancellableOperationBlock) (RNCompletionBlock completion, RNCancelationBlock cancel);

@interface RNConcurrentBlockOperation : NSOperation

@property (nonatomic, strong) NSDictionary *userInfo;

-(instancetype)initWithBlock:(RNOperationBlock)block;
+(instancetype)operationWithBlock:(RNOperationBlock)operationBlock;
-(instancetype)initWithCancellableBlock:(RNCancellableOperationBlock)block;
+(instancetype)operationWithCancellableBlock:(RNCancellableOperationBlock)operationBlock;

@end
