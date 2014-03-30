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

/**
 *  Block that signals the concurrent operation finished..
 *
 *  @param userInfo dictionary that allows the caller to signal the operation has been canceled or store a result to be inspected later in the operation's userInfo property.
 *  @see RNOperationStatusKey
 *  @see RNOperationResultKey
 *  @see RNOperationErrorKey
 */
typedef void (^RNCompletionBlock) (NSDictionary *userInfo);
/**
 *  Block that will be executed by RNConcurrentBlockOperation as a concurrent NSOperation. It will always be started on the main thread.
 *
 *  @param completion block that must be called when finishing or cancelling the operation so it can be properly finalized.
 */
typedef void (^RNOperationBlock) (RNCompletionBlock completion);

/**
 *  Key added to the userInfo dictionary to indicate the operation status. Non existant key or a nil dictionary is interpreted the same as RNOperationStatusFinished.
 */
extern NSString * const RNOperationStatusKey;
/**
 *  Value passed to the userInfo's RNOperationStatusKey to indicate the operation has been canceled
 */
extern NSString * const RNOperationStatusCanceled;
/**
 *  Value passed to the userInfo's RNOperationStatusKey to indicate the operation has succeeded
 */
extern NSString * const RNOperationStatusFinished;

/**
 *  Key added to the userInfo dictionary to store the operation result
 */
extern NSString * const RNOperationResultKey;
/**
 *  Key added to the userInfo dictionary to store a NSError object associated with the operation
 */
extern NSString * const RNOperationErrorKey;

@interface RNConcurrentBlockOperation : NSOperation

/**
 *  Dictionary that is passed to the completion block to influence the operation finish status, and may be inspected after the operation finished to get results or arbitrary data out of it.
 */
@property (nonatomic, strong) NSDictionary *userInfo;

-(instancetype)initWithBlock:(RNOperationBlock)block;
+(instancetype)operationWithBlock:(RNOperationBlock)operationBlock;

@end
