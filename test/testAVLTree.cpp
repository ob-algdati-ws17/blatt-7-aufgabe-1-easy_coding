#include "testAVLTree.h"

using namespace std;

TEST(AVLTreeTest, Test_EmptyTree) {
    AVLTree tree;
    EXPECT_TRUE(tree.isEmpty());
    EXPECT_EQ(nullptr, tree.inorder());
}

TEST(AVLTreeTest, Test_OneValue) {
    AVLTree tree;
    tree.insert(1);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_TRUE(tree.search(1));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1));
}

TEST(AVLTreeTest, Test_TwoValues) {
    AVLTree tree;
    tree.insert(1);
    tree.insert(2);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_TRUE(tree.search(1));
    EXPECT_TRUE(tree.search(2));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1,2));
}

TEST(AVLTreeTest, Test_Rotate_Right) {
    AVLTree tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_TRUE(tree.search(1));
    EXPECT_TRUE(tree.search(2));
    EXPECT_TRUE(tree.search(3));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1,2,3));

}

TEST(AVLTreeTest, Test_Rotate_Left) {
    AVLTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_TRUE(tree.search(1));
    EXPECT_TRUE(tree.search(2));
    EXPECT_TRUE(tree.search(3));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1,2,3));


}

TEST(AVLTreeTest, Test_Rotate_RightLeft) {
    AVLTree tree;
    tree.insert(1);
    tree.insert(3);
    tree.insert(2);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_TRUE(tree.search(1));
    EXPECT_TRUE(tree.search(2));
    EXPECT_TRUE(tree.search(3));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1,2,3));
}

TEST(AVLTreeTest, Test_Rotate_LeftRight) {
    AVLTree tree;
    tree.insert(3);
    tree.insert(1);
    tree.insert(2);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_TRUE(tree.search(1));
    EXPECT_TRUE(tree.search(2));
    EXPECT_TRUE(tree.search(3));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1,2,3));
}

TEST(AVLTreeTest, Test_Rotate_Everything) {
    AVLTree tree;
    // left right
    tree.insert(50);
    tree.insert(30);
    tree.insert(40);
    // right left
    tree.insert(36);
    tree.insert(33);
    // left
    tree.insert(55);
    tree.insert(60);
    // right
    tree.insert(20);
    tree.insert(10);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_TRUE(tree.search(50));
    EXPECT_TRUE(tree.search(30));
    EXPECT_TRUE(tree.search(40));
    EXPECT_TRUE(tree.search(36));
    EXPECT_TRUE(tree.search(33));
    EXPECT_TRUE(tree.search(55));
    EXPECT_TRUE(tree.search(60));
    EXPECT_TRUE(tree.search(20));
    EXPECT_TRUE(tree.search(10));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(10,20,30,33,36,40,50,55,60));
}





