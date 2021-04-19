import sys


def get_hash_partitions(start_hash, end_hash, no_of_div):
        start_hash = int(start_hash,16)
        end_hash = int(end_hash, 16)


        diff = int((end_hash - start_hash)/no_of_div)
       # print("\n DEBUG :")
       # print(hex(diff))

        output = ""
        #step = start_hash;

        
        for _ in range(0, no_of_div):
            end_hash = start_hash + diff - 1
            output = output + hex(start_hash)[2:]
            output = output + " " + hex(end_hash)[2:] + "\n"
            start_hash = start_hash + diff
            
        #print(output)   
        
        file = open("hash-partitions-temp.txt","w")
        file.write(output)
        file.close

        ## exeption handling is remaining



if __name__ == "__main__":
   # print("DEBUG:  @hash_cal.py script")
   # print(sys.argv[0])
   # print(sys.argv[1])
   # print(sys.argv[2])
   # print(sys.argv[3])

    get_hash_partitions(sys.argv[1], sys.argv[2], int(sys.argv[3]))
