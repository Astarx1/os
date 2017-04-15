/* FS : 1024 octets blocks, inode contient 1 numero de champ (chap bloc) qui sert à stocker les numeros des blocs de données
On a les routines bloc_from_disk() et bloc_to disk() et get_free_bloc() */

// Attention c'est contre intuitif. Lorsque l'utilisateur veut read, on doit lui write les données :)
int sifs_read_inode(inode* ino, char* dst, int len, int pos) {
	// On commence par determiner dans quel bloc on ecrit
	id = pos / bloc_size;
	off = pos % bloc_size;

	b = bfd(id);
	// bfd(if):
	// 	b = bloc_from_disk(ino->blocs)
	// 	return bloc_from_disk(b[id])

	si len < bloc_size-off
		copy len de b + off vers dst
	sinon
		copy bloc_size-off de b+off vers dst
		len = len - (bloc_size-off)
		pos = pos + (bloc_size-off)
		dst = dst + (bloc_size-off)
}