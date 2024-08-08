#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100
#define MAX_KEYWORDS 20
#define MAX_KEYWORD_LENGTH 20
#define MAX_KelimeSayisi 100
#define MAX_KelimeUzunlugu 50


// Ahmet Dumanlı-05210000242 Sergen Öztürk-05210000918 Hüseyin Koç-05210000064

struct Variable {
    char type[5];
    char name[31];
    char value[31];
};


void removeComments(const char *input, char *output) {
    int input_len = strlen(input);
    int output_index = 0;
    bool inComment = false;

    for (int i = 0; i < input_len; i++) {
        if (input[i] == '/' && input[i + 1] == '*') {
            inComment = true;
            i++;
        } else if (input[i] == '*' && input[i + 1] == '/') {
            inComment = false;
            i++;
        } else if (!inComment) {
            output[output_index++] = input[i];
        }
    }

    output[output_index] = '\0';
}
void yorumKontrol(char* str) {
    char* startPtr = strstr(str, "/*"); // Başlangıç ifadesi aranıyor
    char* endPtr = strstr(str, "*/"); // Bitiş ifadesi aranıyor

    if (startPtr != NULL) { // Başlangıç ifadesi bulunduysa
        if (endPtr != NULL) { // Bitiş ifadesi de bulunduysa
            printf("Yorum ifadesi tamamlandi.\n");
        } else {
            printf("Hata: Yorum ifadesi tamamlanmamış!\n");
            exit(1);
        }
    }
}

void tekBosluk(char* str) {
    bool bosluk = false;
    int index = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (isspace(str[i])) {
            if (!bosluk) {
                str[index++] = ' ';
                bosluk = true;
            }
        } else {
            str[index++] = str[i];
            bosluk = false;
        }
    }

    str[index] = '\0';
}

void ayir_ve_at(char *str, char *dizi[])
{

    int i = 0;
    char *token = strtok(str, ";");

    while (token != NULL && i < MAX_SIZE)
    {
        dizi[i++] = token;

        token = strtok(NULL, ";");
    }

    // Son ifadenin son karakterini kontrol et
    if (i > 0)
    {
        int son_indeks = strlen(dizi[i-1]) - 1;
        if (dizi[i-1][son_indeks] == ';')
        {
            dizi[i-1][son_indeks] = '\0';
        }
        else
        {
            dizi[i] = NULL; // Son ifadeyi diziye ekleme
        }
    }
}
void trimLeadingSpaces(char* str) {
    size_t length = strlen(str);
    size_t i = 0;

    while (isspace(str[i])) {
        ++i;
    }

    if (i > 0) {
        memmove(str, str + i, length - i + 1);
    }
}

void trimWhitespace(char* str) {
    int length = strlen(str);
    int start = 0;
    int end = length - 1;

    // Başındaki boşlukları atlama
    while (isspace(str[start])) {
        start++;
    }

    // Sonundaki boşlukları atlama
    while (end >= start && isspace(str[end])) {
        end--;
    }

    // Başındaki ve sonundaki boşlukları silme
    int newLength = end - start + 1;
    memmove(str, str + start, newLength);
    str[newLength] = '\0';
}


void removeAfterSemicolon(char *str) {
    trimWhitespace(str);
    int len = strlen(str);
    if (str[len - 1] != ';') {
        printf("Hata: Dizi sonunda ';' karakteri yok.\n");
        return;
    }
    if (len > 0 && str[len - 1] != ';') {
        char *semicolonPtr = strrchr(str, ';');
        if (semicolonPtr != NULL) {
            *(semicolonPtr + 1) = '\0';
        }
    }

}


void stringiBol(const char* string, char kelimeDizisi[MAX_KelimeSayisi][MAX_KelimeUzunlugu], int* kelimeSayisi)
{
    int i = 0;
    char* kelime;

    // İlk kelimeyi al
    kelime = strtok(string, " ");

    // Kelimeleri bölmeye devam et
    while (kelime != NULL && i < MAX_KelimeSayisi)
    {
        strcpy(kelimeDizisi[i], kelime);
        i++;

        // Bir sonraki kelimeyi al
        kelime = strtok(NULL, " ");
    }

    *kelimeSayisi = i;
}

bool startsWithNew(const char* str) {
    const char* substring = "new";
    size_t substringLength = strlen(substring);

    if (strncmp(str, substring, substringLength) == 0) {
        return true;
    }

    return false;
}

bool startsWithKeywords(const char* str) {
    const char* keywords[] = {"input ", "output ", "write ", "read ","new "};
    size_t numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    for (size_t i = 0; i < numKeywords; ++i) {
        size_t keywordLength = strlen(keywords[i]);

        if (strncmp(str, keywords[i], keywordLength) == 0) {
            return true;
        }
    }

    return false;
}

void setVariable(struct Variable* var, const char* second, const char* third, struct Variable variables[]) {
    strncpy(var->name, third, sizeof(var->name) - 1);
    var->name[sizeof(var->name) - 1] = '\0';
    if (strcmp(second, "int") == 0) {
        strncpy(var->type, "int", sizeof(var->type) - 1);
        var->type[sizeof(var->type) - 1] = '\0';
    } else if (strcmp(second, "text") == 0) {
        strncpy(var->type, "text", sizeof(var->type) - 1);
        var->type[sizeof(var->type) - 1] = '\0';
    } else {
        printf("Hata: Gecersiz type degeri\n");
        return;
    }
}

void removeQuotes(char* str) {
    int length = strlen(str);

    if (length >= 2 && str[0] == '"' && str[length - 1] == '"') {
        memmove(str, str + 1, length - 2);
        str[length - 2] = '\0';
    }
}

void removeFirstQuote(char* string) {
    if (string[0] == '"') {
        memmove(string, string + 1, strlen(string));
    }
}

void removeLastQuote(char* string) {
    int length = strlen(string);
    if (length > 0 && string[length - 1] == '"') {
        string[length - 1] = '\0';
    }
}
int isNumeric(const char* string) {
    int i = 0;
    while (string[i] != '\0') {
        if (!isdigit(string[i])) {
            return 0; // Sayısal değil
        }
        i++;
    }

    return 1; // Sayısal
}
int isAlphaNumeric(const char *str) {
    while (*str) {
        if (!isalnum(*str)) {
            return 0; // Alfasayısal olmayan karakter var, 0 döndür
        }
        str++;
    }
    return 1; // Tüm karakterler alfasayısal, 1 döndür
}

void calculateAddition(char* str, int degisken_sayisi, struct Variable variables[]) {
    // + işaretini bulma
    char* plus = strchr(str, '+');
    if (plus != NULL) {
        // '+' işaretinin sol ve sağ operandlarını belirleme
        char* leftOperandEnd = plus - 1;
        char* rightOperandStart = plus + 1;

        // Sol operandu geçici bir diziye kopyalama
        size_t leftOperandLength = leftOperandEnd - str + 1;
        char* leftOperand = malloc(leftOperandLength + 1);
        strncpy(leftOperand, str, leftOperandLength);
        leftOperand[leftOperandLength] = '\0';

        // Sol operanddan boşlukları atlayarak sayıyı bulma
        char* leftOperandPtr = leftOperand;
        while (*leftOperandPtr && isspace(*leftOperandPtr)) {
            leftOperandPtr++;
        }
        trimWhitespace(leftOperandPtr);
        if(isNumeric(leftOperandPtr) == 0){

            for(int i = 0; i < degisken_sayisi; i++){
                if(strcmp(variables[i].name, leftOperandPtr) == 0){
                    strcpy(leftOperandPtr, variables[i].value);
                    break;
                }
            }
        }



        // Sağ operandu geçici bir diziye kopyalama
        size_t rightOperandLength = strlen(rightOperandStart);
        char* rightOperand = malloc(rightOperandLength + 1);
        strcpy(rightOperand, rightOperandStart);

        // Sağ operanddan boşlukları atlayarak sayıyı bulma
        char* rightOperandPtr = rightOperand;
        while (*rightOperandPtr && isspace(*rightOperandPtr)) {
            rightOperandPtr++;
        }
        trimWhitespace(rightOperandPtr);

        if(isNumeric(rightOperandPtr) == 0){
            for(int i = 0; i < degisken_sayisi; i++){
                if(strcmp(variables[i].name, rightOperandPtr) == 0){
                    strcpy(rightOperandPtr, variables[i].value);
                    break;
                }
            }
        }
        if(isNumeric(leftOperandPtr) != 0 && isNumeric(rightOperandPtr) != 0){
            int leftValue = atoi(leftOperandPtr);
            int rightValue = atoi(rightOperandPtr);
            int result = leftValue + rightValue;
            sprintf(str, "%d", result);
        }



        // Toplama işlemi ve sonucun stringe dönüştürülmesi


        if(isNumeric(leftOperandPtr) == 0 && isNumeric(rightOperandPtr) == 0){
            removeFirstQuote(rightOperandPtr);
            removeLastQuote(leftOperandPtr);

            strcpy(str, leftOperandPtr);
            strcat(str, rightOperandPtr);
        }

        // Bellekte ayrılan hafızayı serbest bırakma
        free(leftOperand);
        free(rightOperand);
    }
}

void concatenateStrings(char* str, int degisken_sayisi, struct Variable variables[]) {
    int length = strlen(str);
    int plusIndex = -1;

    // + işareti kontrolü
    for (int i = 0; i < length; i++) {
        if (str[i] == '+') {
            plusIndex = i;
            break;
        }
    }

    // + işareti bulunamadıysa veya + işaretinden sonra ifade yoksa
    if (plusIndex == -1 || plusIndex == length - 1) {
        printf("Hatalı ifade: + işareti bulunamadı veya + işaretinden sonra ifade yok\n");
        return;
    }

    char substr1[20];
    char substr2[20];

    strncpy(substr1, str, plusIndex);  // + işaretinden önceki substring
    substr1[plusIndex] = '\0';

    strncpy(substr2, str + plusIndex + 1, length - (plusIndex + 1));  // + işaretinden sonraki substring
    substr2[length - (plusIndex + 1)] = '\0';

    trimWhitespace(substr1);
    trimWhitespace(substr2);

    for(int i = 0; i < degisken_sayisi; i++){
        if(strcmp(variables[i].name, substr1) == 0 && strcmp(variables[i].type, "text") == 0){
            strcpy(substr1, variables[i].value);
        }
    }
    for(int i = 0; i < degisken_sayisi; i++){
        if(strcmp(variables[i].name, substr2) == 0 && strcmp(variables[i].type, "text") == 0){
            strcpy(substr2, variables[i].value);
        }
    }
    removeFirstQuote(substr2);
    removeLastQuote(substr2);
    removeFirstQuote(substr1);
    removeLastQuote(substr1);

    strcpy(str, substr1);
    strcat(str, substr2);


}

void calculateSubtraction(char* str, int degisken_sayisi, struct Variable variables[]) {
    // - işaretini bulma
    char* minus = strchr(str, '-');
    if (minus != NULL) {
        // - işaretinin sol ve sağ operandlarını belirleme
        char* leftOperandEnd = minus - 1;
        char* rightOperandStart = minus + 1;

        // Sol operandun sonundaki boşlukları silme
        while (leftOperandEnd > str && *leftOperandEnd == ' ') {
            leftOperandEnd--;
        }

        // Sağ operandın başındaki boşlukları silme
        while (*rightOperandStart == ' ') {
            rightOperandStart++;
        }

        // Sol ve sağ operandların uzunluklarını hesaplama
        size_t leftLength = leftOperandEnd - str + 1;
        size_t rightLength = strlen(rightOperandStart);

        // Sol ve sağ operandları kopyalama
        char* leftOperand = malloc(leftLength + 1);
        char* rightOperand = malloc(rightLength + 1);
        strncpy(leftOperand, str, leftLength);
        strncpy(rightOperand, rightOperandStart, rightLength);

        // Null karakterlerini ekleme
        leftOperand[leftLength] = '\0';
        rightOperand[rightLength] = '\0';

        trimWhitespace(leftOperand);
        trimWhitespace(rightOperand);

        for(int i = 0; i < degisken_sayisi; i++){
                if(strcmp(variables[i].name, leftOperand) == 0){
                    strcpy(leftOperand, variables[i].value);
                    break;
                }
            }
        for(int i = 0; i < degisken_sayisi; i++){
                if(strcmp(variables[i].name, rightOperand) == 0){
                    strcpy(rightOperand, variables[i].value);
                    break;
                }
            }


        if(isNumeric(leftOperand) != 0 && isNumeric(rightOperand) != 0){
            // Sol ve sağ operandları sayıya çevirme
            int leftValue = atoi(leftOperand);
            int rightValue = atoi(rightOperand);

            // Sol operandın sağ operanddan küçük olduğunu kontrol etme
            if (leftValue < rightValue) {
                printf("Hata: Negatif değerler desteklenmiyor.\n");
                return;
            } else {
                // İşlemi yapma ve sonucu stringe dönüştürme
                int result = leftValue - rightValue;
                sprintf(str, "%d", result);
            }
        }
        else if(isNumeric(leftOperand) == 0 && isNumeric(rightOperand) == 0){
            char* found = strstr(leftOperand, rightOperand);
            if (found != NULL) {
                // Soldaki stringin içinden sağdaki stringi çıkar
                memmove(found, found + strlen(rightOperand), strlen(found) - strlen(rightOperand) + 1);
                strcpy(str, leftOperand);
            }else {
                printf("Sagdaki string soldaki stringin icinde bulunamadi.\n");
            }
        }


        // Bellekte ayrılan hafızayı serbest bırakma
        free(leftOperand);
        free(rightOperand);
    }
}

void processString(const char* string) {
    const char* delim = "-";
    char* leftToken;
    char* rightToken;

    // İlk '-' karakterin sağını ve solunu ayrı ifadeler olarak al
    leftToken = strtok(strdup(string), delim);
    rightToken = strtok(NULL, delim);

    // Soldaki ve sağdaki ifadelerin başındaki ve sonundaki boşlukları atla
    while (*leftToken == ' ') {
        leftToken++;
    }
    while (*rightToken == ' ') {
        rightToken++;
    }
    int leftLen = strlen(leftToken);
    int rightLen = strlen(rightToken);
    while (leftLen > 0 && leftToken[leftLen - 1] == ' ') {
        leftToken[leftLen - 1] = '\0';
        leftLen--;
    }
    while (rightLen > 0 && rightToken[rightLen - 1] == ' ') {
        rightToken[rightLen - 1] = '\0';
        rightLen--;
    }

    // İlk ve son karakterlerin çift tırnak işareti olduğunu kontrol et
    if (leftToken[0] == '"' && leftToken[leftLen - 1] == '"' &&
        rightToken[0] == '"' && rightToken[rightLen - 1] == '"') {

        // Çift tırnak arasındaki ifadeyi al
        char* leftSubstring = strdup(leftToken + 1);
        leftSubstring[leftLen - 2] = '\0';
        char* rightSubstring = strdup(rightToken + 1);
        rightSubstring[rightLen - 2] = '\0';

        // Soldaki string içinde sağdaki stringin olup olmadığını kontrol et
        char* found = strstr(leftSubstring, rightSubstring);
        if (found != NULL) {
            // Soldaki stringin içinden sağdaki stringi çıkar
            memmove(found, found + strlen(rightSubstring), strlen(found) - strlen(rightSubstring) + 1);
            strcpy(string, leftSubstring);
        } else {
            printf("Sagdaki string soldaki stringin içinde bulunamadi.\n");
        }

        free(leftSubstring);
        free(rightSubstring);
    } else {
        printf("Hatali giris: Ilk ve son karakterler cift tirnak isareti olmalı.\n");
        strcpy(string, "");
        return;
    }


    free(leftToken);
}

void sizeFunction(const char* string, int size, struct Variable variables[]) {
    const char* p = string;
    char valueOfVariable[30];
    char result[20];
    // Kontrol edilecek ifadenin "size(" ile başladığından emin olunur
    if (strncmp(p, "size(", 5) != 0) {
        strcpy(result, ""); // Geçersiz ifade, boş string atanır.
        return;
    }

    p += 5; // "size(" ifadesini atla

    // Parantez içindeki karakterleri alır ve result ifadesine yazılır
    int index = 0;

    while (*p != ')' && *p != '\0') {
        result[index] = *p;
        index++;
        p++;
    }

    // Sonlandırıcı karakter eklenir
    result[index] = '\0';

    char length[2];




     for(int k = 0; k < size; k++){
        if(strcmp(result, variables[k].name) == 0){
            strcpy(valueOfVariable, variables[k].value);

        }

    }
    sprintf(length, "%d", strlen(valueOfVariable));
    strcpy(string, length);

}
void subsFunction(char* string, int size, struct Variable variables[]) {
    const char* p = string;
    char valueOfVariable1[30];
    char valueOfVariable2[30];
    char valueOfVariable3[30];
    char result[20];
    int resultCount = 0;

    // Kontrol edilecek ifadenin "subs(" ile başladığından emin olunur
    if (strncmp(p, "subs(", 5) != 0) {
        strcpy(string, ""); // Geçersiz ifade, boş string atanır.
        return;
    }

    p += 5; // "subs(" ifadesini atla

    // Parantez içindeki karakterleri alır ve result ifadesine yazılır
    int index = 0;

    while (*p != '\0') {

        if ((*p == ',') || (*p == ')' && resultCount == 2) || (*p == ')')) {
            result[index] = '\0';
            index = 0;
            resultCount++;

            if (resultCount > 3) {
                strcpy(string, ""); // Hatalı ifade, boş string atanır.
                printf("Yanlış argüman hatası!");
                exit(1);
            }

            if (resultCount == 1) {
                // result1 için arama yap
                int found = 0;
                for (int k = 0; k < size; k++) {
                    if (strcmp(result, variables[k].name) == 0) {
                        strcpy(valueOfVariable1, variables[k].value);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(valueOfVariable1, result);
                     // Eşleşme bulunamazsa direkt değeri al
                }
            } else if (resultCount == 2) {
                // result2 için arama yap
                int found = 0;
                for (int k = 0; k < size; k++) {
                    if (strcmp(result, variables[k].name) == 0) {
                        strcpy(valueOfVariable2, variables[k].value);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(valueOfVariable2, result); // Eşleşme bulunamazsa direkt değeri al
                }
            } else if (resultCount == 3) {
                // result3 için arama yap
                int found = 0;
                for (int k = 0; k < size; k++) {
                    if (strcmp(result, variables[k].name) == 0) {
                        strcpy(valueOfVariable3, variables[k].value);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(valueOfVariable3, result); // Eşleşme bulunamazsa direkt değeri al
                }
            }
        } else {
            result[index] = *p;
            index++;
        }

        p++;
    }

    // Sonlandırıcı karakter eklenir
    result[index] = '\0';

    if (resultCount != 3) {
        printf("Missing required argument 'end' in subs function call!\n");
        strcpy(string, ""); // Hatalı ifade, boş string atanır.
        return;
    }

    // valueOfVariable1'nin valueOfVariable2 indexinden valueOfVariable3 indexine kadar olan kısmını bul
    int start = atoi(valueOfVariable2);
    int end = atoi(valueOfVariable3);

    if (start < 0 || start >= strlen(valueOfVariable1) || end <= start || end > strlen(valueOfVariable1)) {
        strcpy(string, ""); // Geçersiz indis aralığı, boş string atanır.
        return;
    }

    strncpy(string, valueOfVariable1 + start, end - start + 1);
    string[end - start + 1] = '\0';

}

void locateFunction(char* string, int size, struct Variable variables[]) {
    const char* p = string;
    char valueOfVariable1[30];
    char valueOfVariable2[30];
    char valueOfVariable3[30];
    char result[20];
    int resultCount = 0;

    // Kontrol edilecek ifadenin "process(" ile başladığından emin olunur
    if (strncmp(p, "locate(", 7) != 0) {
        strcpy(string, ""); // Geçersiz ifade, boş string atanır.
        return;
    }

    p += 7; // "process(" ifadesini atla

    // Parantez içindeki karakterleri alır ve result ifadesine yazılır
    int index = 0;

    while (*p != '\0') {

        if ((*p == ',')  || (*p == ')'))  {
            result[index] = '\0';
            trimLeadingSpaces(result);
            removeQuotes(result);
            index = 0;
            resultCount++;

            if (resultCount > 3) {
                strcpy(string, ""); // Hatalı ifade, boş string atanır.
                return;
            }

            if (resultCount == 1) {
                // result1 için arama yap
                int found = 0;
                for (int k = 0; k < size; k++) {
                    if (strcmp(result, variables[k].name) == 0) {
                        strcpy(valueOfVariable1, variables[k].value);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(valueOfVariable1, result);
                }
            } else if (resultCount == 2) {
                // result2 için arama yap
                int found = 0;
                for (int k = 0; k < size; k++) {
                    if (strcmp(result, variables[k].name) == 0) {
                        strcpy(valueOfVariable2, variables[k].value);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(valueOfVariable2, result);
                }
            } else if (resultCount == 3) {
                // result3 için arama yap
                int found = 0;
                for (int k = 0; k < size; k++) {
                    if (strcmp(result, variables[k].name) == 0) {
                        strcpy(valueOfVariable3, variables[k].value);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(valueOfVariable3, result);
                }
            }
        } else {
            result[index] = *p;
            index++;
        }

        p++;
    }

    // Sonlandırıcı karakter eklenir
    result[index] = '\0';

    if (resultCount != 3) {
        strcpy(string, ""); // Hatalı ifade, boş string atanır.
        return;
    }

    // valueOfVariable1'nin valueOfVariable3 indexinden valueOfVariable2 indexine kadar olan kısmını bul
    int start = atoi(valueOfVariable3);
    const char* substr = strstr(valueOfVariable1 + start, valueOfVariable2);

    if (substr == NULL) {
        strcpy(string, ""); // Bulunamadı, boş string atanır.
        return;
    }

    int indexFound = substr - valueOfVariable1;
    snprintf(string, sizeof(string), "%d", indexFound);

}

void insertFunction(char* string, int size, struct Variable variables[]) {
    const char* p = string;

    // Kontrol edilecek ifadenin "insert(" ile başladığından emin olunur
    if (strncmp(p, "insert(", 7) != 0) {
        strcpy(string, ""); // Geçersiz ifade, boş string atanır.
        return;
    }

    p += 7; // "insert(" ifadesini atla

    // Parantez içindeki karakterleri alır ve parametrelere atar
    char parameter1[30];
    char parameter2[30];
    char parameter3[30];
    int paramIndex = 0;
    int paramCount = 0;

    while (*p != ')' && *p != '\0') {
        if (*p == ',') {
            if (paramCount == 0){
                parameter1[paramIndex] = '\0';
                trimLeadingSpaces(parameter1);
            }else if (paramCount == 1){
                parameter2[paramIndex] = '\0';
                trimLeadingSpaces(parameter2);
            }else if (paramCount == 2){
                parameter3[paramIndex] = '\0';
                trimLeadingSpaces(parameter3);
            }
            paramIndex = 0;
            paramCount++;
        } else {
            switch (paramCount) {
                case 0:
                    parameter1[paramIndex] = *p;
                    break;
                case 1:
                    parameter2[paramIndex] = *p;
                    break;
                case 2:
                    parameter3[paramIndex] = *p;
                    break;
            }
            paramIndex++;
        }

        p++;
    }

    // Sonlandırıcı karakter eklenir
    if (paramCount == 0){
        parameter1[paramIndex] = '\0';
    }
    else if (paramCount == 1){
        parameter2[paramIndex] = '\0';
    }else if (paramCount == 2){
        parameter3[paramIndex] = '\0';
        trimLeadingSpaces(parameter3);
        removeQuotes(parameter3);
    }
    if (paramCount != 2) {
        strcpy(string, ""); // Hatalı ifade, boş string atanır.
        return;
    }

    // Değişkenlerin değerlerini ara veya doğrudan ata
    char valueOfVariable1[30];
    char valueOfVariable2[30];
    char valueOfVariable3[30];
    int found1 = 0;
    int found2 = 0;
    int found3 = 0;

    for (int i = 0; i < size; i++) {
        if (strcmp(parameter1, variables[i].name) == 0) {
            strcpy(valueOfVariable1, variables[i].value);
            found1 = 1;
        }

        if (strcmp(parameter2, variables[i].name) == 0) {
            strcpy(valueOfVariable2, variables[i].value);
            found2 = 1;
        }

        if (strcmp(parameter3, variables[i].name) == 0) {
            strcpy(valueOfVariable3, variables[i].value);
            found3 = 1;
        }
    }

    if (!found1)
        strcpy(valueOfVariable1, parameter1);
    if (!found2)
        strcpy(valueOfVariable2, parameter2);
    if (!found3)
        strcpy(valueOfVariable3, parameter3);

    // Yerleştirme işlemini gerçekleştir
    int insertIndex = atoi(valueOfVariable2);
    int valueOfVariable1Length = strlen(valueOfVariable1);
    int valueOfVariable3Length = strlen(valueOfVariable3);

    if (insertIndex < 0 || insertIndex > valueOfVariable1Length) {
        strcpy(string, ""); // Geçersiz indeks, boş string atanır.
        return;
    }

    int newStringLength = valueOfVariable1Length + valueOfVariable3Length;
    char newString[60];
    strncpy(newString, valueOfVariable1, insertIndex);
    strncpy(newString + insertIndex, valueOfVariable3, valueOfVariable3Length);
    strncpy(newString + insertIndex + valueOfVariable3Length, valueOfVariable1 + insertIndex, valueOfVariable1Length - insertIndex);
    newString[newStringLength] = '\0';

    strcpy(string, newString);
}

void overrideFunction(char* string, int size, struct Variable variables[]) {
    const char* p = string;
    char valueOfVariable1[30];
    char valueOfVariable2[30];
    char valueOfVariable3[30];
    char result[20];
    int resultCount = 0;

    // Kontrol edilecek ifadenin "override(" ile başladığından emin olunur
    if (strncmp(p, "override(", 9) != 0) {
        strcpy(string, ""); // Geçersiz ifade, boş string atanır.
        return;
    }

    p += 9; // "override(" ifadesini atla

    // Parantez içindeki karakterleri alır ve result ifadesine yazılır
    int index = 0;

    while (*p != ')' && *p != '\0') {

        if (*p == ',') {
            result[index] = '\0';
            trimLeadingSpaces(result);
            removeQuotes(result);
            index = 0;
            resultCount++;

            if (resultCount > 3) {
                strcpy(string, ""); // Hatalı ifade, boş string atanır.
                return;
            }

            if (resultCount == 1) {
                // result1 için arama yap
                int found = 0;
                for (int k = 0; k < size; k++) {
                    if (strcmp(result, variables[k].name) == 0) {
                        strcpy(valueOfVariable1, variables[k].value);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(valueOfVariable1, result); // Eşleşme bulunamazsa direkt değeri al
                }
            } else if (resultCount == 2) {
                // result2 için arama yap
                int found = 0;
                for (int k = 0; k < size; k++) {
                    if (strcmp(result, variables[k].name) == 0) {
                        strcpy(valueOfVariable2, variables[k].value);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(valueOfVariable2, result); // Eşleşme bulunamazsa direkt değeri al
                }
            } else if (resultCount == 3) {
                // result3 için arama yap
                int found = 0;
                for (int k = 0; k < size; k++) {
                    if (strcmp(result, variables[k].name) == 0) {
                        strcpy(valueOfVariable3, variables[k].value);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(valueOfVariable3, result);
                    // Eşleşme bulunamazsa direkt değeri al
                }
            }
        } else {
            result[index] = *p;

            index++;
        }

        p++;
    }



    if (*p == ')' && resultCount == 2) {
        // Sonlandırıcı karakter eklenir
        result[index] = '\0';
        trimLeadingSpaces(result);
        removeQuotes(result);
        int found = 0;
        for (int k = 0; k < size; k++) {
            if (strcmp(result, variables[k].name) == 0) {
                strcpy(valueOfVariable3, variables[k].value);
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(valueOfVariable3, result);
            // Eşleşme bulunamazsa direkt değeri al
        }

    }
    else{
        strcpy(string, ""); // Hatalı ifade, boş string atanır.
        return;
    }



    // valueOfVariable1'in başından valueOfVariable2 kadar olan kısmını al
    int start = atoi(valueOfVariable2);

    if (start < 0 || start >= strlen(valueOfVariable1)) {
        strcpy(string, ""); // Geçersiz indis aralığı, boş string atanır.
        return;
    }

    char temp1[100];
    char temp2[100];
    strncpy(temp1, valueOfVariable1, start);
    temp1[start] = '\0';
    strncpy(temp2, valueOfVariable1 + start + strlen(valueOfVariable3), strlen(string) - (start + strlen(valueOfVariable3)));
    temp2[strlen(string) - (start + strlen(valueOfVariable3))] = '\0';

    // valueOfVariable3'ü sonuna ekle
    strcat(temp1, valueOfVariable3);
    strcat(temp1, temp2);
    strcpy(string,temp1);
}

void asString(char* str, int size, struct Variable variables[]) {
    // İstenilen formatı kontrol et
    if (strlen(str) < 10 || strncmp(str, "asString(", 9) != 0 || str[strlen(str)-1] != ')') {
        printf("Hatalı giriş! Geçerli bir asString ifadesi giriniz.\n");
        return;
    }

    // İçerisindeki değişkeni al
    char varName[100];
    strncpy(varName, str+9, strlen(str)-10);
    varName[strlen(str)-10] = '\0';

    // Değişkeni bul
    int i;
    int found = 0;
    for (i = 0; i < size; i++) {
        if (strcmp(variables[i].name, varName) == 0) {
            found = 1;
            break;
        }
    }

    // Değişken bulunamadıysa hata ver
    if (!found) {
        printf("Hata: %s değişkeni bulunamadi!\n", varName);
        return;
    }

    // Değişkenin tipini kontrol et
    if (strcmp(variables[i].type, "int") != 0) {
        printf("Hata: %s degiskeninin tipi int degil!\n", varName);
        return;
    }

    // Tipi "text" olarak güncelle
    strcpy(variables[i].type, "text");

    // Değişkenin değerini kontrol et
    if (strcmp(variables[i].value, "") == 0) {
        strcpy(str, "");
    } else {
        strcpy(str, variables[i].value);
    }

    printf("Ifadenin tipi basariyla guncellendi\n", str);
}

void asText(char* str, int size, struct Variable variables[]) {
    // İstenilen formatı kontrol et
    if (strlen(str) < 9 || strncmp(str, "asText(", 7) != 0 || str[strlen(str)-1] != ')') {
        printf("Hatalı giriş! Geçerli bir asText ifadesi giriniz.\n");
        return;
    }

    // İçerisindeki değişkeni al
    char varName[100];
    strncpy(varName, str+7, strlen(str)-8);
    varName[strlen(str)-8] = '\0';

    // Değişkeni bul
    int i;
    int found = 0;
    for (i = 0; i < size; i++) {
        if (strcmp(variables[i].name, varName) == 0) {
            found = 1;
            break;
        }
    }

    // Değişken bulunamadıysa hata ver
    if (!found) {
        printf("Hata: %s değişkeni bulunamadı!\n", varName);
        return;
    }

    // Değişkenin tipini kontrol et
    if (strcmp(variables[i].type, "text") != 0) {
        printf("Hata: %s değişkeninin tipi text değil!\n", varName);
        return;
    }

    // Tipi "int" olarak güncelle
    strcpy(variables[i].type, "int");

    // asText ifadesini güncelle
    strcpy(str, variables[i].value);

    printf("asText ifadesi basariyla guncellendi: %s\n", str);
}
char* dosyaOku(const char* dosyaAdi) {
    // Bu fonksiyon çağrıldığında okuyacağınız dosyanın ismini bilgisayardaki tam konumuyla beraber vermeniz gerekmektedir!

    FILE* dosya = fopen(dosyaAdi, "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi.\n");
        return NULL;
    }

    // Dosyanın boyutunu öğrenmek için dosyanın sonuna gidip konumunu alıyoruz
    fseek(dosya, 0, SEEK_END);
    long dosyaBoyutu = ftell(dosya);

    // Dosyanın başına dönüp içeriği okuma
    fseek(dosya, 0, SEEK_SET);

    // Bellekte string için yer ayırma
    char* icerik = (char*)malloc((dosyaBoyutu + 1) * sizeof(char));
    if (icerik == NULL) {
        printf("Bellek ayirma hatasi.\n");
        fclose(dosya);
        return NULL;
    }

    // Dosyayı stringe okuma
    size_t okunan = fread(icerik, sizeof(char), dosyaBoyutu, dosya);
    if (okunan != dosyaBoyutu) {
        printf("Dosya okuma hatasi.\n");
        fclose(dosya);
        free(icerik);
        return NULL;
    }

    icerik[dosyaBoyutu] = '\0'; // Null karakter ile sonlandırma

    fclose(dosya);

    return icerik;
}

void stringDosyayaYaz(const char* string, const char* dosyaYolu) {
    FILE* dosya = fopen(dosyaYolu, "w");
    if (dosya == NULL) {
        printf("Dosya acilamadi!");
        return;
    }

    fprintf(dosya, "%s", string);
    fclose(dosya);
}
char* getUserInput(const char* promptText) {
    static char inputBuffer[101];  // 100 karakterlik bir tampon
    printf("%s\n", promptText);
    fgets(inputBuffer, sizeof(inputBuffer), stdin);

    // Satır sonu karakterini kaldır
    size_t length = strlen(inputBuffer);
    if (inputBuffer[length - 1] == '\n') {
        inputBuffer[length - 1] = '\0';
    }

    return inputBuffer;
}

int diziElemanSayisi(int dizi[]) {
    int elemanSayisi = sizeof(dizi) / sizeof(dizi[0]);
    return elemanSayisi;
}





int main()
{
    struct Variable variables[1000];
    int degisken_sayisi = 0;
    int size = diziElemanSayisi(variables);


    while(1){


    char input[1000];

    char output[1000];

    printf("Giris metnini girin: ");
    fgets(input, sizeof(input), stdin);
    yorumKontrol(input);
    input[strcspn(input, "\n")] = '\0';  // Son satırda eklenen '\n' karakterini kaldırma

    removeComments(input, output);

    tekBosluk(output);

    char *dizi[MAX_SIZE];
    removeAfterSemicolon(output);
    int kelimeSayisi = 0;


    ayir_ve_at(output,dizi);

    char kelimeDizisi[MAX_KelimeSayisi][MAX_KelimeUzunlugu];

    for (int i = 0; dizi[i] != NULL; i++)
    {
        trimLeadingSpaces(dizi[i]);
        char* str = dizi[i];
        char* result = strstr(str, ":=");
        char subStr1[31];
        char subStr2[100];
        if(startsWithKeywords(dizi[i])){
            stringiBol(dizi[i], kelimeDizisi, &kelimeSayisi);
            if(strcmp(kelimeDizisi[0],"new") == 0){

                if(isAlphaNumeric(kelimeDizisi[2]) == 0){
                    printf("Degisken isminde gecersiz karakter kullanimi!\n");
                    break;
                }
                if(strlen(kelimeDizisi[2]) > 31){
                    printf("Variable name exceeds the maximum size of 30 characters!\n");
                    break;
                }

                setVariable(&variables[degisken_sayisi], kelimeDizisi[1], kelimeDizisi[2], variables);
                degisken_sayisi ++;
            }
            else if(strcmp(kelimeDizisi[0],"read") == 0 && strcmp(kelimeDizisi[2],"from") ==  0){
                int size2 =  diziElemanSayisi(variables);
                for(int i = 0; i < degisken_sayisi; i++){
                    if(strcmp(kelimeDizisi[1], variables[i].name) == 0 && strcmp(variables[i].type, "text") == 0){
                        char dosyaIsmi[100];
                        for(int k = 0; k < degisken_sayisi; k++){
                            if(strcmp(kelimeDizisi[3], variables[k].name) == 0){
                                strcpy(dosyaIsmi, variables[k].value);
                                break;
                            }
                            else{
                                strcpy(dosyaIsmi, kelimeDizisi[3]);
                            }
                        }
                        strcpy(variables[i].value, dosyaOku(dosyaIsmi));
                    }
                }

            }
            else if(strcmp(kelimeDizisi[0], "write") == 0 && strcmp(kelimeDizisi[2], "to") == 0){
                int size3 = diziElemanSayisi(variables);
                for(int i = 0; i < degisken_sayisi; i++){
                    if(strcmp(kelimeDizisi[1], variables[i].name) == 0 && strcmp(variables[i].type, "text") == 0){
                        char dosyaIsmi[100];
                        for(int k = 0; k < degisken_sayisi; k++){
                            if(strcmp(kelimeDizisi[3], variables[k].name) == 0){
                                strcpy(dosyaIsmi, variables[k].value);
                                break;
                            }
                            else{
                                strcpy(dosyaIsmi, kelimeDizisi[3]);
                            }
                        }
                        stringDosyayaYaz(variables[i].value, dosyaIsmi);
                        printf("Metin dosyaya yazildi.");


                    }
                }
            }
            else if(strcmp(kelimeDizisi[0], "input") == 0 && strcmp(kelimeDizisi[2], "prompt") == 0){
                 int size4 = diziElemanSayisi(variables);
                 for(int i = 0; i < size4; i++){
                    if(strcmp(kelimeDizisi[3], variables[i].name) == 0 && strcmp(variables[i].type, "text") == 0){
                        strcpy(variables[i].value, getUserInput(variables[i].value));
                    }
                 }
            }
            else if(strcmp(kelimeDizisi[0], "output") == 0){
                int size5 = diziElemanSayisi(variables);
                 for(int i = 0; i < degisken_sayisi; i++){
                    if(strcmp(kelimeDizisi[1], variables[i].name) == 0){
                        printf("Sonuc :%s\n", variables[i].value);
                    }
                    else if(strstr(kelimeDizisi[1], "asString(") != NULL){
                        asString(kelimeDizisi[1], degisken_sayisi, variables);
                        printf("Sonuc :%s\n", kelimeDizisi[1]);
                    }
                 }
            }
        }


        else if(result != NULL){

            int position = result - str;

            strcpy(subStr1,"");
            strcpy(subStr2,"");

            strncpy(subStr1, str, position);
            strncpy(subStr2, str + (position + 3), strlen(str) - (position + 2));

            subStr1[position] = '\0';

            trimWhitespace(subStr1);
            trimWhitespace(subStr2);

            if(strchr(subStr2, '-') != NULL && strchr(subStr2, '"') == NULL){
                calculateSubtraction(subStr2, degisken_sayisi, variables);

            }
            if(strchr(subStr2, '+') != NULL && strchr(subStr2, '"') == NULL){
                calculateAddition(subStr2, degisken_sayisi, variables);
            }
            if(strchr(subStr2, '"') != NULL){
                if(strchr(subStr2, '+') != NULL){
                    concatenateStrings(subStr2, degisken_sayisi, variables);
                }
                if(strchr(subStr2, '-') != NULL){
                        processString(subStr2);
                }

            }


            if(strstr(subStr2, "size(") != NULL){
                sizeFunction(subStr2, size, variables);
            }
            if(strstr(subStr2, "subs(") != NULL){

                subsFunction(subStr2, degisken_sayisi, variables);
            }
            if(strstr(subStr2, "locate(") != NULL){
                locateFunction(subStr2, degisken_sayisi, variables);
            }

            if(strstr(subStr2, "insert(") != NULL){

                insertFunction(subStr2, degisken_sayisi, variables);
            }
            if(strstr(subStr2, "override(") != NULL){
                overrideFunction(subStr2, degisken_sayisi, variables);
            }
            if(strstr(subStr2, "asString(") != NULL){
                asString(subStr2, degisken_sayisi, variables);
            }
            if(strstr(subStr2, "asText(") != NULL){
                asText(subStr2, size, variables);
            }
            int find = 0;
            for(int k = 0; k < degisken_sayisi; k++){
                if(strcmp(subStr1, variables[k].name) == 0){
                    find = 1;
                    if(strcmp(variables[k].type, "int") == 0 && isNumeric(subStr2) == 0){
                        printf("Tip uyusmazligi hatasi!\n");
                        break;
                    }
                    else if(strcmp(variables[k].type, "int") == 0 && subStr2 < 0){
                        printf("Negatif sayilar desteklenmiyor!\n");
                        break;
                    }

                    else if(strchr(subStr2, '"') != NULL){
                        removeQuotes(subStr2);
                    }
                    strcpy(variables[k].value, subStr2);
                }
            }
        }
    }
}


 return 0;
}
