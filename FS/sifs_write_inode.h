/* FS : 1024 octets blocks, inode contient 1 numero de champ (chap bloc) qui sert à stocker les numeros des blocs de données
On a les routines bloc_from_disk() et bloc_to disk() et get_free_bloc() */
int sifs_write_inode(inode* ino, const char* src, int len, int pos) {
	bid = bl_f_d(ino->blocs);
	while (len > 0)
		id = pos/bsize;
		off = pos%bsize;
		b = bl_f_d (bid[id]);
		if (len < bsize - off)
			copy len from src to b+off
			len = 0
		else
			copy bsize-off from src to b + off
			len = len - (bsize-off)
			src = src + (bsize-off)
}