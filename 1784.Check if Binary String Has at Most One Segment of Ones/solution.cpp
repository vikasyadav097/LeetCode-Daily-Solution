#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int base_price;
    int demand_factor;
    long long discount_num; // discount_rate * 10 as integer (e.g. 2.5 -> 25)
    long long eff_disc_x1000; // base_price * discount_rate_x10 (avoids float entirely)
} Product;

Product prods[1000];

int compare(const void *a, const void *b) {
    Product *p1 = (Product *)a;
    Product *p2 = (Product *)b;
    
    // 1. Higher effective discount first (integer comparison, no float errors)
    if (p2->eff_disc_x1000 != p1->eff_disc_x1000)
        return (p2->eff_disc_x1000 > p1->eff_disc_x1000) ? 1 : -1;
    
    // 2. Higher demand factor first
    if (p2->demand_factor != p1->demand_factor)
        return p2->demand_factor - p1->demand_factor;
    
    // 3. Lower product ID first
    return p1->id - p2->id;
}

void user_logic(int products[][4], int n, int *sorted_product_ids) {
    qsort(prods, n, sizeof(Product), compare);
    for (int i = 0; i < n; i++) {
        sorted_product_ids[i] = prods[i].id;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    int products[n][4];
    
    for (int i = 0; i < n; i++) {
        // Read discount_rate as string and parse to avoid float imprecision
        int id, base_price, demand_factor;
        char rate_str[20];
        scanf("%d %d %s %d", &id, &base_price, rate_str, &demand_factor);
        
        // Parse "2.5" -> integer 25 (multiply by 10)
        // Parse "10" -> integer 100
        // Parse "5" -> integer 50
        long long rate_x10 = 0;
        int found_dot = 0;
        int decimal_places = 0;
        
        for (int j = 0; rate_str[j] != '\0'; j++) {
            if (rate_str[j] == '.') {
                found_dot = 1;
            } else {
                rate_x10 = rate_x10 * 10 + (rate_str[j] - '0');
                if (found_dot) {
                    decimal_places++;
                    if (decimal_places == 1) break; // only need 1 decimal place
                }
            }
        }
        // If no decimal found, multiply by 10 to normalize
        if (!found_dot) rate_x10 *= 10;
        
        prods[i].id = id;
        prods[i].base_price = base_price;
        prods[i].demand_factor = demand_factor;
        prods[i].discount_num = rate_x10;
        // eff_disc proportional to base_price * rate_x10 (= base_price * rate * 10)
        prods[i].eff_disc_x1000 = (long long)base_price * rate_x10;
        
        products[i][0] = id;
        products[i][1] = base_price;
        products[i][2] = (int)rate_x10;
        products[i][3] = demand_factor;
    }
    
    int sorted_product_ids[n];
    user_logic(products, n, sorted_product_ids);
    
    for (int i = 0; i < n; i++) {
        printf("%d ", sorted_product_ids[i]);
    }
    printf("\n");
    return 0;
}