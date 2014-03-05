RNConcurrentBlockOperation
==========================

RNConcurrentBlockOperation is a simple NSOperation subclass, similar to NSBlockOperation. It allows a block of work that is potentially asynchrounous to be submited into a NSOperationQueue for parallel execution.


Sample usage:
```Objective-C
  NSOperationQueue *queue = [NSOperationQueue new];
  queue.maxConcurrentOperations = 5;
  RNConcurrentBlockOperation *asyncOperation = [RNConcurrentBlockOperation operationWithBlock:^(RNCompletionBlock completion) {
    //Some async operation
    //... ... ...
    //Async operation completed
    completion();
  }];
  [queue addOperation:asyncOperation];
  //New in 1.0.1 cancellable operation support
  [queue addOperation:[RNConcurrentBlockOperation operationWithCancellableBlock:^(RNCompletionBlock completion, RNCancelationBlock cancel) {
    //Some async operation
    //... ... ...
    //pass the cancellation block along to some UI element and let it cancel the operation anytime
    [self setCancellationHandler:cancel];
    //Async operation completed
    completion();
  }]];
  
