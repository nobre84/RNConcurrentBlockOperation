RNConcurrentBlockOperation
==========================

RNConcurrentBlockOperation is a simple NSOperation subclass, similar to NSBlockOperation. It allows a block of work that is potentially asynchrounous to be submited into a NSOperationQueue for parallel execution.


Sample usage:
```Objective-C
  NSOperationQueue *queue = [NSOperationQueue new];
  queue.maxConcurrentOperations = 5;
  RNConcurrentBlockOperation *asyncOperation = [RNConcurrentBlockOperation operationWithBlock:^(void(^completion)(void)){
    //Some async operation
    //... ... ...
    //Async operation completed
    completion();
  }];
  [queue addOperation:asyncOperation];
