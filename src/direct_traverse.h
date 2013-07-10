#ifndef Y_DIRECT_TRAVERSE_H
#define Y_DIRECT_TRAVERSE_H


/* @function: 遍历文件夹
 * @recurse: == 0 非递归 != 0 递归
 */
int direct_traverse(const char *direct, int recurs, int (*visit)(char *file, void *handle_ptr, void *bak_path), 
				void *handle_ptr, void *bak_path);


#endif /* Y_DIRECT_TRAVERSE_H */
