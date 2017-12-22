#include "testAVLTree.h"

using namespace std;

TEST(AVLTreeTest, Test_EmptyTree) {
    AVLTree tree;
    EXPECT_TRUE(tree.isEmpty());
    EXPECT_EQ(nullptr, tree.inorder());
    EXPECT_EQ(nullptr, tree.preorder());
    EXPECT_EQ(nullptr, tree.postorder());
}

TEST(AVLTreeTest, Test_OneValue) {
    AVLTree tree;
    tree.insert(1);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_TRUE(tree.search(1));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(1));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(1));
}

TEST(AVLTreeTest, Test_TwoValues) {
    AVLTree tree;
    tree.insert(1);
    tree.insert(2);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_TRUE(tree.search(1));
    EXPECT_TRUE(tree.search(2));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1, 2));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(1, 2));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(2, 1));
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
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1, 2, 3));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(2, 1, 3));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(1, 3, 2));

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
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1, 2, 3));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(2, 1, 3));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(1, 3, 2));


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
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1, 2, 3));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(2, 1, 3));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(1, 3, 2));
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
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1, 2, 3));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(2, 1, 3));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(1, 3, 2));
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
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(10, 20, 30, 33, 36, 40, 50, 55, 60));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(40, 33, 20, 10, 30, 36, 55, 50, 60));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(10, 30, 20, 36, 33, 50, 60, 55, 40));
}

TEST(AVLTreeTest, Test_Remove_One_Then_Empty) {
    AVLTree tree;
    tree.insert(1);
    EXPECT_FALSE(tree.isEmpty());
    tree.remove(1);
    EXPECT_TRUE(tree.isEmpty());
    EXPECT_EQ(nullptr, tree.inorder());
    EXPECT_EQ(nullptr, tree.preorder());
    EXPECT_EQ(nullptr, tree.postorder());
}

TEST(AVLTreeTest, Test_Remove_One_Then_One_Left) {
    AVLTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.remove(2);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(1));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(1));
}

TEST(AVLTreeTest, Test_Remove_Without_Child_Without_Rotation) {
    AVLTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.remove(3);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(1, 2));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(2, 1));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(1, 2));
}

TEST(AVLTreeTest, Test_Remove_Without_Child_RightLeft_Rotation) {
    AVLTree tree;
    tree.insert(40);
    tree.insert(30);
    tree.insert(50);
    tree.insert(45);
    tree.remove(30);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(40, 45, 50));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(45, 40, 50));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(40, 50, 45));
}

TEST(AVLTreeTest, Test_Remove_Without_Child_Left_Rotation) {
    AVLTree tree;
    tree.insert(40);
    tree.insert(30);
    tree.insert(50);
    tree.insert(55);
    tree.remove(30);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(40, 50, 55));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(50, 40, 55));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(40, 55, 50));
}

TEST(AVLTreeTest, Test_Remove_Without_Child_LeftRight_Rotation) {
    AVLTree tree;
    tree.insert(40);
    tree.insert(30);
    tree.insert(50);
    tree.insert(35);
    tree.remove(50);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(30, 35, 40));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(35, 30, 40));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(30, 40, 35));
}

TEST(AVLTreeTest, Test_Remove_Without_Child_Right_Rotation) {
    AVLTree tree;
    tree.insert(40);
    tree.insert(30);
    tree.insert(50);
    tree.insert(25);
    tree.remove(50);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(25, 30, 40));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(30, 25, 40));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(25, 40, 30));
}

TEST(AVLTreeTest, Test_Remove_Without_Child_Critical) {
    AVLTree tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(25);
    tree.insert(5);
    tree.insert(14);
    tree.insert(26);
    tree.insert(12);
    tree.remove(26);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(5, 10, 12, 14, 20, 25));
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(14, 10, 5, 12, 20, 25));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(5, 12, 10, 25, 20, 14));
}



//TEST(AVLTreeTest, Test_Remove_With_One_Child_Left) {
//    AVLTree tree;
//    tree.insert(10);
//    tree.insert(20);
//    tree.insert(30);
//    tree.insert(25);
//    tree.remove(30);
//    EXPECT_FALSE(tree.isEmpty());
//    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(10, 20, 25));
//    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(20, 10, 25));
//    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(10, 25, 20));
//}
//
//
//TEST(AVLTreeTest, Test_Remove_With_Two_Childs) {
//    AVLTree tree;
//    tree.insert(40);
//    tree.insert(30);
//    tree.insert(50);
//    tree.insert(45);
//    tree.remove(40);
//    EXPECT_FALSE(tree.isEmpty());
//    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(30, 45, 50));
//    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(45, 30, 50));
//    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(30, 50, 45));
//}




