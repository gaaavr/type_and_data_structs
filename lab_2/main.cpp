#include <iostream>

double calculateSquareByLeftRectangle(double, double, int);

double calculateSquareByRightRectangle(double, double, int);

double calculateSquareByTrapeze(double xmin, double xmax, int n);

double testFunc(double x);

void modeWithoutAccuracy(double xmin, double xmax);

void modeWithAccuracy(double xmin, double xmax);

int main() {
    double xmin, xmax;

    printf("Введите Xmin:\n");
    scanf("%lf", &xmin);

    printf("Введите Xmax:\n");
    scanf("%lf", &xmax);

    if (xmin >= xmax) {
        printf("Xmin должен быть строго меньше Xmax\n");
        exit(1);
    }

    modeWithoutAccuracy(xmin, xmax);
    modeWithAccuracy(xmin, xmax);

    return 0;
}

double calculateSquareByLeftRectangle(double xmin, double xmax, int n) {
    double h = (xmax - xmin) / n;
    double s = 0.0, current_x = xmin;

    for (int i = 0; i < n - 1; i++) {
        s += abs(testFunc(current_x) * h);
        current_x += h;
    }

    s += abs((testFunc(current_x) * (xmax - current_x)));

    return s;
}

double calculateSquareByRightRectangle(double xmin, double xmax, int n) {
    double h = (xmax - xmin) / n;
    double s = 0.0, current_x = xmax;

    for (int i = 0; i < n - 1; i++) {
        s += abs(testFunc(current_x) * h);
        current_x -= h;
    }

    s += abs((testFunc(current_x) * (current_x-xmin)));

    return s;
}

double calculateSquareByTrapeze(double xmin, double xmax, int n) {
    double h = (xmax - xmin) / n;
    double s = 0.0, current_x_left = xmin, current_x_right = current_x_left+h;

    for (int i = 0; i < n - 1; i++) {
        s += (((abs(testFunc(current_x_left)) + abs(testFunc(current_x_right))) / 2) * h);
        current_x_left += h;
        current_x_right += h;
    }

    s += (((abs(testFunc(current_x_left)) + abs(testFunc(current_x_right))) / 2) * (xmax - xmin - ((n - 1) * h)));

    return s;
}


double testFunc(double x) {
    return (x / 8) + sin(x);
}

void modeWithoutAccuracy(double xmin, double xmax) {
    printf("[Расчёт интеграла без точности]\n");
    int n;

    printf("Введите N:\n");
    scanf("%d", &n);

    if (n < 1) {
        printf("N должен быть строго больше 0\n");
        exit(1);
    }

    printf("[Метод левых прямоугольников] площадь под графиком равна %lf\n",
           calculateSquareByLeftRectangle(xmin, xmax, n));
    printf("[Метод правых прямоугольников] площадь под графиком равна %lf\n",
           calculateSquareByRightRectangle(xmin, xmax, n));
    printf("[Метод трапеций] площадь под графиком равна %lf\n",
           calculateSquareByTrapeze(xmin, xmax, n));

    printf("\n");
}

void modeWithAccuracy(double xmin, double xmax) {
    printf("[Расчёт интеграла с точностью]\n");

    int n;
    double eps;

    printf("Введите эпсилон (необходимую точность вычислений):\n");
    scanf("%lf", &eps);

    if (eps >= 1 || eps <= 0) {
        printf("эпсилон должен быть строго меньше 1 и строго больше 0\n");
        exit(1);
    }

    printf("Введите N для расчёта интеграла с заданной точностью:\n");
    scanf("%d", &n);

    if (n < 1) {
        printf("N должен быть строго больше 0\n");
        exit(1);
    }

    // ограничим количество итераций, чтобы не возникло бесконечного
    // цикла в случае, если интеграл не сходится
    int n_max = 10000;
    double prev_result, cur_result;

    prev_result = calculateSquareByLeftRectangle(xmin, xmax, n);
    for (int i = n + 1; i < n_max; i++) {
        if (i == n_max - 1) {
            printf("[Метод левых прямоугольников] интеграл площади не сошёлся из-за достижения максимального количества итераций\n");
            break;
        }

        cur_result = calculateSquareByLeftRectangle(xmin, xmax, i);

        if (abs(prev_result - cur_result) <= eps) {
            printf("[Метод левых прямоугольников] площадь с заданной точностью %lf под графиком равна %lf\n",
                   eps, cur_result);
            break;
        }
        prev_result=cur_result;
    }

    prev_result = calculateSquareByRightRectangle(xmin, xmax, n);
    for (int i = n + 1; i < n_max; i++) {
        if (i == n_max - 1) {
            printf("[Метод правых прямоугольников] интеграл площади не сошёлся из-за достижения максимального количества итераций\n");
            break;
        }

        cur_result = calculateSquareByRightRectangle(xmin, xmax, i);

        if (abs(prev_result - cur_result) <= eps) {
            printf("[Метод правых прямоугольников] площадь с заданной точностью %lf под графиком равна %lf\n",
                   eps, cur_result);
            break;
        }

        prev_result=cur_result;
    }

    prev_result = calculateSquareByTrapeze(xmin, xmax, n);
    for (int i = n + 1; i < n_max; i++) {
        if (i == n_max - 1) {
            printf("[Метод трапеций] интеграл площади не сошёлся из-за достижения максимального количества итераций\n");
            break;
        }

        cur_result = calculateSquareByTrapeze(xmin, xmax, i);

        if (abs(prev_result - cur_result) <= eps) {
            printf("[Метод трапеций] площадь с заданной точностью %lf под графиком равна %lf\n",
                   eps, cur_result);
            break;
        }
        prev_result=cur_result;
    }
}