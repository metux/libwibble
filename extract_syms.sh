# from libtool... don't wonder
function sym2decl() {
symcode='[[ABCDGIRSTW]]'
tee sym2decl.out | sed -n -e 's/^T \(.*\)$/\1()/p' -e "s/^$symcode* \(.*\)$/\1/p"
}

# extract symbol list from archive, filter out junk
function extract_raw_syms() {
nm $1 | grep -v '^[^.]*.o:$' | cut -c10- | grep -v '^$' | sort | uniq
}

# convert the raw symbol names to C declarations, filter out more junk
function extract_sym_decls() {
extract_raw_syms $1 | sym2decl | grep -v '\.'
}

# drop the () from declaration, when we want to reference it in a table
function sym_reference() {
sed -e 's,()$,,'
}

# write out symbol declarations
echo 'extern "C" {'
extract_sym_decls $1 | while read s; do echo "extern int $s;"; done
echo '}'

# write out reference to each symbol into an array named like our 2nd argument
cat <<EOF
typedef void *symptr;
symptr $2[] = {
EOF
extract_sym_decls $1 | sym_reference | while read s; do echo "(symptr) &$s,"; done
echo "(symptr) 0 };"

# ... we did it
