#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD 256
#define MAX_MEANING 512

typedef struct {
    char EnglishWord[MAX_WORD];
    char VietnameseMeaning[MAX_MEANING];
} WORD;

// Ham nhap tu dien
void AddWord(FILE *file) {
    WORD word;
    printf("Nhap tu tieng Anh: ");
    scanf("%s", word.EnglishWord);
    printf("Nhap nghia tieng Viet: ");
    getchar(); // Doc ky tu thua
    gets(word.VietnameseMeaning);

    fprintf(file, "%s\t%s\n", word.EnglishWord, word.VietnameseMeaning);
    printf("Da them tu vao tu dien.\n");
}

// Ham xuat tu dien
void DisplayDictionary(FILE *file) {
    char EnglishWord[MAX_WORD];
    char VietnameseMeaning[MAX_MEANING];

    printf("Tu dien:\n");

    while (fscanf(file, "%s\t%s", EnglishWord, VietnameseMeaning) != EOF) {
        printf("Tu: %s\tNghia: %s\n", EnglishWord, VietnameseMeaning);
    }
}

// Ham sap xep theo tu dien tieng anh
void SortDictionary(FILE *file) {
    // Sap xep tap tin tam thoi
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Loi khi mo tep tam thoi.\n");
        return;
    }

    WORD words[1000];

    int count = 0;
    char EnglishWord[MAX_WORD];
    char VietnameseMeaning[MAX_MEANING];

    rewind(file); // Quay lai dau tep goc

    while (fscanf(file, "%s\t%s", EnglishWord, VietnameseMeaning) != EOF) {
        strcpy(words[count].EnglishWord, EnglishWord);
        strcpy(words[count].VietnameseMeaning, VietnameseMeaning);
        count++;
    }

    // Sap xep mang cac tu theo tieng anh
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(words[i].EnglishWord, words[j].EnglishWord) > 0) {
                WORD temp = words[i];
                words[i] = words[j];
                words[j] = temp;
            }
        }
    }

    // Ghi lai vao tep tam thoi da sap xep
    for (int i = 0; i < count; i++) {
        fprintf(tempFile, "%s\t%s\n", words[i].EnglishWord, words[i].VietnameseMeaning);
    }

    fclose(file);
    fclose(tempFile);

    // Doi ten tep tam thoi thanh ten goc
    remove("Dictionary.txt");
    rename("temp.txt", "Dictionary.txt");

    printf("Da sap xep tu dien theo tieng Anh.\n");
}

// Ham tim kiem tu trong tu dien
void SearchWord(FILE *file, char *searchWord) {
    char EnglishWord[MAX_WORD];
    char VietnameseMeaning[MAX_MEANING];
    int found = 0;

    rewind(file); // Quay lai dau tep goc

    while (fscanf(file, "%s\t%s", EnglishWord, VietnameseMeaning) != EOF) {
        if (strcmp(EnglishWord, searchWord) == 0) {
            printf("Tu: %s\tNghia: %s\n", EnglishWord, VietnameseMeaning);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Khong tim thay tu trong tu dien.\n");
    }
}

// Ham cap nhat nghia cua tu trong tu dien
void UpdateMeaning(FILE *file, char *updateWord) {
    char EnglishWord[MAX_WORD];
    char VietnameseMeaning[MAX_MEANING];
    int updated = 0;

    rewind(file); // Quay lai dau tep goc

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Loi khi mo tep tam thoi.\n");
        return;
    }

    while (fscanf(file, "%s\t%s", EnglishWord, VietnameseMeaning) != EOF) {
        if (strcmp(EnglishWord, updateWord) == 0) {
            printf("Nhap nghia moi cua tu: ");
            getchar(); // Doc ky tu enter thua
            gets(VietnameseMeaning);
            updated = 1;
        }

        fprintf(tempFile, "%s\t%s\n", EnglishWord, VietnameseMeaning);
    }

    fclose(file);
    fclose(tempFile);

    // Doi ten tep tam thoi thanh ten goc
    remove("Dictionary.txt");
    rename("temp.txt", "Dictionary.txt");

    if (updated) {
        printf("Da cap nhat nghia cua tu trong tu dien.\n");
    } else {
        printf("Khong tim thay tu de cap nhat.\n");
    }
}

// Ham xoa tu trong tu dien
void DeleteWord(FILE *file, char *deleteWord) {
    char EnglishWord[MAX_WORD];
    char VietnameseMeaning[MAX_MEANING];
    int deleted = 0;

    rewind(file); // Quay lai dau tep goc

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Loi khi mo tep tam thoi.\n");
        return;
    }

    while (fscanf(file, "%s\t%s", EnglishWord, VietnameseMeaning) != EOF) {
        if (strcmp(EnglishWord, deleteWord) == 0) {
            deleted = 1;
            continue; // Bo qua tu can xoa
        }

        fprintf(tempFile, "%s\t%s\n", EnglishWord, VietnameseMeaning);
    }

    fclose(file);
    fclose(tempFile);

    // Doi ten tep tam thoi thanh ten goc
    remove("Dictionary.txt");
    rename("temp.txt", "Dictionary.txt");

    if (deleted) {
        printf("Da xoa tu khoi tu dien.\n");
    } else {
        printf("Khong tim thay tu de xoa.\n");
    }
}

int main() {
    FILE *file;
    file = fopen("Dictionary.txt", "a+");

    if (file == NULL) {
        printf("Khong the mo file.\n");
        return 1;
    }

    int choice;
    char word[MAX_WORD];

    do {
        printf("_______________________________\n");
        printf("1. Them tu\n");
        printf("2. Xuat tu dien\n");
        printf("3. Sap xep tu dien theo tieng Anh\n");
        printf("4. Tim kiem tu\n");
        printf("5. Cap nhat nghia tu\n");
        printf("6. Xoa tu\n");
        printf("7. Thoat\n");
        printf("_______________________________\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                AddWord(file);
                break;
            case 2:
                DisplayDictionary(file);
                break;
            case 3:
                SortDictionary(file);
                break;
            case 4:
                printf("Nhap tu can tim kiem: ");
                scanf("%s", word);
                SearchWord(file, word);
                break;
            case 5:
                printf("Nhap tu can cap nhat: ");
                scanf("%s", word);
                UpdateMeaning(file, word);
                break;
            case 6:
                printf("Nhap tu can xoa: ");
                scanf("%s", word);
                DeleteWord(file, word);
                break;
            case 7:
                printf("Ket thuc chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
                break;
        }
    } while (choice != 7);

    fclose(file);

    return 0;
}