
// old but perfectly working code
#if DEBUG == 1
printf("curr %d, min_key %d\n", curr->key, min_right_subtree_node->key);
#endif

// deal with the min_node, find prev
Node *prev_min_node_ptr =
    prev_min_node(curr->right, min_right_subtree_node->key);
#if DEBUG == 1
printf("prev %d\n",
       prev_min_node_ptr == NULL ? -1 : prev_min_node_ptr->key);
#endif

// update curr
curr->key = min_right_subtree_node->key;

if (prev_min_node_ptr == NULL) {
    assert(curr->right == min_right_subtree_node);
    curr->right = min_right_subtree_node->right;
    free(min_right_subtree_node);
} else {
    assert(prev_min_node_ptr->left == min_right_subtree_node);
    prev_min_node_ptr->left = min_right_subtree_node->right;
    free(min_right_subtree_node);
}
