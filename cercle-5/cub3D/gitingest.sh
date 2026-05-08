# Clear or create the digest.txt
> digest.txt

# Find and process files ONLY in include and src folders
find includes srcs -type f \( -name "*.c" -o -name "*.h" \) | while read -r file; do
    echo "// File: $file" >> digest.txt
    
    cat "$file" | \
    perl -0777 -pe 's/\/\*.*?\*\///gs' | \
    sed 's/\/\/.*//g' | \
    grep -v '^[[:space:]]*#' | \
    grep -v '^[[:space:]]*$' >> digest.txt
    
    echo -e "\n" >> digest.txt
done

# Final count
echo "Token count (excluding comments/headers):"
wc -w digest.txt