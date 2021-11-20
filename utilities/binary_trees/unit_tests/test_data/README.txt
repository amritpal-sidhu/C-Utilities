The files containing test data for binary trees are oganized in the following way:

    input file:
        
        Each line contains a character denoting an operation along with a space separated parameter.
        The types of operations are:
            'i' - insert
            'd' - delete
            'f' - find
        
        Example format of 3 insertions then 1 deletion:
            i 10
            i 5
            i 15
            d 5
        
    output file:

        Each line contains space separated values for a current inorder traversal.
        This string can be thought as the state of the tree to validate operations are
        performed correctly.

        Example syntax for the above sequence with a binary search tree:
            10
            5 10
            5 10 15
            10 15

        For the red black tree, expected node syntax should be provided in the following way:
            <value>:<color>

        For the avl tree, expected node syntax should be provided in the following way:
            <value>:<height>
        
Caveats:

    - This process can be error prone if files are not kept synchronized and free of mistakes.
    - Using files might not be an ideal testing methodology.