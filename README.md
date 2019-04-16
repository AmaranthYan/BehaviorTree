# BehaviorTree

BehaviorTree project in C++ that I wrote for fun xD
## Nodes
Tree node types
### Tree
+ **BehaviorTree**
### Composite
+ **Selector**
+ **Sequence**
+ **Parallel**  
tick all subtrees each time  
*StopOnFail* : stop and return when one subtree fails
### Decorator
+ **Loop**  
loop X times or infinite loop
+ **UntilSuccess**
+ **UntilFailure**
+ **BlackboardComparator**  
compare two blackboard entries or compare one entry to value  
*AbortMode* : suspend or abort subtree when comparison fails
+ **BlackboardCondition**  
detect if blackboard key is set  
*AbortMode* : suspend or abort subtree when condition fails
### Action
+ **Action**  
base class of all actions
## Blackboard
Storage of key-value pairs with observers
### Operations
+ Set
+ Get
+ Has
+ Remove
+ RegisterObserver
+ UnregisterObserver
### Data Types
+ int
+ float
+ bool  

can support other built-in/custom data types
## Example
An agent is roaming around in 1D space and can be interrupted by pressing the **SPACE** key  
  
![ExampleTreeGraph](https://github.com/AmaranthYan/BehaviorTree/blob/master/BehaviorTree/Example/Example_graph.png)
