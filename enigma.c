#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define NUM_ROTORS 8

/* Array of rotors */
const char* enigma_rotors[NUM_ROTORS+1] = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ", //0
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ", //1
    "AJDKSIRUXBLHWTMCQGZNPYFVOE", //2
    "BDFHJLCPRTXVZNYEIWGAKMUSQO", //3
    "ESOVPZJAYQUIRHXLNFTGKDCMWB", //4
    "UKLBEPXWJVFZIYGAHCMTONDRQS", //5
    "JPGVOUMFYQBENHZRDKASXLICTW", //6
    "NZJHGRCXMYSWBOUFAIVLPEKQDT", //7
    "FKQHTLXOCBJSPDZRAMEWNIUYGV"  //8
};

/*
 * Convert a space-separated string of rotor indices into
 * an integer array of rotor indices
 *
 * @param rotor_ind_str   Space-separated string of rotor indices
 * @param num_rotors      Number of rotors provided in the string
 * @return                Integer array of rotor indices
 */
int* parse_rotor_indices(char* rotor_ind_str, int num_rotors) {
    // TODO
      int* rotor_indices = (int*)malloc(num_rotors * sizeof(int));
      if (rotor_indices == NULL){
          return NULL;
      }
  
      int index = 0;
      for (int i = 0; rotor_ind_str[i] != '\0'; i++){
          if (rotor_ind_str[i] >= '0' && rotor_ind_str[i] <= '9'){
              rotor_indices[index++] = rotor_ind_str[i] - '0';
              if (index == num_rotors){
                  break;
                }
            }
        }
      if (index != num_rotors){
        free(rotor_indices);
          return NULL;
      }
  
      return rotor_indices;
  }



/*
 * Create a 2D array of integers where
 * each row represents a rotor
 *
 * @param rotors          Integer array of rotor indices
 * @param num_rotors      Number of rotors provided
 * @return                2D array where each row represents a rotor
 */
int** set_up_rotors(int* rotors, int num_rotors) {
    // TODO
    int** rotor_array = (int**)malloc(num_rotors * sizeof(int*));
    if (rotor_array == NULL){
        return NULL;
    }

    for (int i = 0; i < num_rotors; i++){
        
        rotor_array[i] = (int*)malloc(26 * sizeof(int));
        if (rotor_array[i] == NULL){
            
            for (int j = 0; j < i; j++){
                free(rotor_array[j]);
            }
            free(rotor_array);
            return NULL;
        }

        for (int k = 0; k < 26; k++){
            rotor_array[i][k] = enigma_rotors[rotors[i]][k] - 'A';
        }
   }

    return rotor_array;
}


/*
 * Rotate each rotor to the right by the
 * given number of rotations
 *
 * @param rotor_config   2D array of rotors
 * @param rotations      Number of rotations
 * @param num_rotors     Number of rotors provided
 */
void rotate_rotors(int** rotor_config, int rotations, int num_rotors) {
    // TODO
    rotations %= 26;
    
    if (rotations == 0){
        return;
    }

    for (int i = 0; i < num_rotors; i++){
        
       for (int j = 0; j < rotations; j++){
           int last = rotor_config[i][25];
           
           for (int k = 25; k > 0; k--){
               rotor_config[i][k] = rotor_config[i][k-1];
           }

           rotor_config[i][0] = last;
       }

    }
}
/*
 * Encrypt the given message
 *
 * @param message        Message to encrypt
 * @param rotor_config   2D array of rotors
 * @param num_rotors     Number of rotors provided
 * @return               Encrypted message
 */
char* encrypt(char *message, int** rotor_config, int num_rotors) {
    // TODO
    int i = 0;
    while (message[i] != '\0'){
        i++;
    }

    char* encrypted = (char*)malloc((i+1) * sizeof(char));
    if (encrypted == NULL) {
        return NULL;
    }

    i = 0;
    while (message[i] != '\0'){
        char ch = message[i];

        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')){
            if (ch >= 'a' && ch <= 'z'){
                ch = ch - ('a' - 'A');
            }
            int index = ch - 'A';
            
            for (int r = 0; r < num_rotors; r++){
                index = rotor_config[r][index];
            }

            encrypted[i] = 'A' + index;
        } else{
            encrypted[i] = ch;
        }
        i++;
    }

    encrypted[i] = '\0';
    printf("Encrypted message: "); 
    return encrypted;
}

/*
 * Decrypt the given message
 *
 * @param message        Message to decrypt
 * @param rotor_config   2D array of rotors
 * @param num_rotors     Number of rotors provided
 * @return               Decrypted message
 */
char* decrypt(char *message, int** rotor_config, int num_rotors) {
    // TODO
    int i = 0;
    while (message[i] != '\0'){
        i++;
    }

    char* decrypted = (char*)malloc((i+1) * sizeof(char));
    if (decrypted == NULL){
        return NULL;
    }

    i = 0;
    while (message[i] != '\0'){
        char ch = message[i];

        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')){
            if (ch >= 'a' && ch <= 'z'){
                ch = ch - ('a' - 'A');
            }

            int index = ch - 'A';
            

            for (int r = 0; r < num_rotors; r++) {
                int original_index = -1;
                

                for (int j = 0; j < 26; j++) {
                    if (rotor_config[r][j] == index) {
                        original_index = j;
                        break;
                    }
                }
                if (original_index != -1){
                    index = original_index;
                }

            }
            decrypted[i] = 'A' + index;


        } else {
            decrypted[i] = ch;
        }
        i++;
    }

    decrypted[i] = '\0';
    printf("Decrypted message: "); 
    return decrypted;
}

/*
 * Format of command line input:
 * ./enigma e "JAVA" 3 "1 2 4" 0
 * 
 *    e    - mode (e for encrypt, d for decrypt)
 * "JAVA"  - message
 *    3    - number of rotors to use
 * "1 2 4" - indices of rotors to use
 *    0    - number of rotations of the rotors
 */
int main(int argc, char* argv[]) {
    // TODO
    if (argc != 6){
        printf("Usage: %s <mode> <message> <num_rotors> <rotor_indices> <rotations>\n", argv[0]);
        return 1;
    }

    char mode = argv[1][0];
    char* message = argv[2];
    int num_rotors = atoi(argv[3]);
    char* rotor_indices_str = argv[4];
    int rotations = atoi(argv[5]);

    if (mode != 'e' && mode != 'd'){
        printf("Error: Invalid mode. Use 'e' to encrypt and 'd' to decrypt.\n");
        return 1;
    }

    int* rotor_indices = parse_rotor_indices(rotor_indices_str, num_rotors);
    if (rotor_indices == NULL){
        printf("Error: failed to parse indices.\n");
        return 1;
    }

    int** rotor_config = set_up_rotors(rotor_indices, num_rotors);
    if (rotor_config == NULL){
        printf("Error: Failed to set up rotors.\n");
        free(rotor_indices);
        return 1;
    }
    
    rotate_rotors(rotor_config, rotations, num_rotors);

    char* result;
    if (mode == 'e'){
        result = encrypt(message, rotor_config, num_rotors);
    } else{
        result = decrypt(message, rotor_config, num_rotors);
    }

    if (result == NULL){
        free(rotor_indices);
        for (int i = 0; i < num_rotors; i++){
            free(rotor_config[i]);
        }
        free(rotor_config);
        return 1;
    }
    
    printf("%s\n", result);

    free(rotor_indices);
    free(result);
    for (int i = 0; i < num_rotors; i++){
        free(rotor_config[i]);
    }
    free(rotor_config);

    return 0;
}





