#ifndef Y_DIRECT_TRAVERSE_H
#define Y_DIRECT_TRAVERSE_H


/* @function: �����ļ���
 * @recurse: == 0 �ǵݹ� != 0 �ݹ�
 */
int direct_traverse(const char *direct, int recurs, int (*visit)(char *file, void *handle_ptr, void *bak_path), 
				void *handle_ptr, void *bak_path);


#endif /* Y_DIRECT_TRAVERSE_H */
