#include "kulki.h"
bool clickedBall = false, movedBall = true, gameOver = false, deleted;
int x, y, px, py, los, p1, p2, p3;
GtkWidget* plansza;
GtkWidget* kolejneKulki;
GtkWidget* prevButton;
GtkWidget* sumPoints;
GtkWidget* przyciskM;
int board[9][9];
int nextB[3];
int sumapkt = 0;
int nextB[3];\

void saveGame(GtkWidget* save)
{
    FILE *wfile;
    wfile = fopen("save.txt", "w");
    fprintf(wfile, "%d\n", sumapkt);
    fprintf(wfile, "%d%d%d\n", nextB[0], nextB[1], nextB[2]);
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            fprintf(wfile, "%d", board[i][j]);
        }
    }
    fclose(wfile);
    gtk_label_set_text(GTK_LABEL(przyciskM), "Zapisano grę!\n");
}

void loadGame(GtkWidget* load)
{
    FILE *rfile;
    rfile = fopen("save.txt", "r");
    if(rfile == NULL)
    {
        gtk_label_set_text(GTK_LABEL(przyciskM), "Brak zapisu gry!\n");
        return;
    }

    gtk_label_set_text(GTK_LABEL(przyciskM), "Wczytano grę!\n");

    int znak;

    //wynik
    int wynik = 0;
    while((znak=fgetc(rfile))!='\n')
    {
        wynik *= 10;
        wynik += znak - '0';
    }
    sumapkt = wynik;
    gtk_button_set_label(GTK_BUTTON(sumPoints), intToString(sumapkt));

    //nastepne kulki
    for(int i=0; i<3; i++)
    {
        znak = fgetc(rfile) - '0';
        gtk_button_set_image(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(kolejneKulki), i, 0)), putColorM(znak));
    }
    znak = fgetc(rfile);

    //plansza
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            znak = fgetc(rfile) - '0';
            board[i][j] = znak;
            gtk_button_set_image(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(plansza), j, i)), putColor(znak-1));
        }
    }
    fclose(rfile);
}

char* intToString(int n)
{
    char str[100000];
    sprintf(str, "%d", n);
    return strdup(str);
}

void putNextBalls()
{
    nextBalls();
    for(int i=0; i<3; i++)
    {
        gtk_button_set_image(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(kolejneKulki), i, 0)), putColorM(nextB[i]));
    }
}

void nextBalls()
{
    for(int i=0; i<3; i++)
    {
        nextB[i] = colorNum();
    }
}

void deleteCorrectRow(int a, int b)
{
    int suma = 0, x = a, y = b, licznik;
    int kulka = board[x][y];
    deleted = false;

    //POZIOM
    licznik = 1;
    while(y-1>=0 && board[x][y-1]==kulka)
    {
        licznik++;
        y--;
    }
    y = b;
    while(y+1<=8 && board[x][y+1]==kulka)
    {
        licznik++;
        y++;
    }
    y = b;
    if(licznik>=5)
    {
        suma+=licznik-1;
        deleted = true;
        while(y-1>=0 && board[x][y-1]==kulka)
        {
            gtk_button_set_image(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(plansza), y-1, x)), NULL);
            board[x][y-1] = 0;
            y--;
        }
        y = b;
        while(y+1<=8 && board[x][y+1]==kulka)
        {
            gtk_button_set_image(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(plansza), y+1, x)), NULL);
            board[x][y+1] = 0;
            y++;
        }
    }
    y = b;

    //PION
    licznik = 1;
    while(x-1>=0 && board[x-1][y]==kulka)
    {
        licznik++;
        x--;
    }
    x = a;
    while(x+1<=8 && board[x+1][y]==kulka)
    {
        licznik++;
        x++;
    }
    x = a;
    if(licznik>=5)
    {
        suma+=licznik-1;
        deleted = true;
        while(x-1>=0 && board[x-1][y]==kulka)
        {
            gtk_button_set_image(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(plansza), y, x-1)), NULL);
            board[x-1][y] = 0;
            x--;
        }
        x = a;
        while(x+1<=8 && board[x+1][y]==kulka)
        {
            gtk_button_set_image(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(plansza), y, x+1)), NULL);
            board[x+1][y] = 0;
            x++;
        }
    }
    x = a;

    //LEWY SKOS
    licznik = 1;
    while(x-1>=0 && y-1>=0 && board[x-1][y-1]==kulka)
    {
        licznik++;
        x--;
        y--;
    }
    x = a;
    y = b;
    while(x+1<=8 && y+1<=8 && board[x+1][y+1]==kulka)
    {
        licznik++;
        x++;
        y++;
    }
    x = a;
    y = b;
    if(licznik>=5)
    {
        suma+=licznik-1;
        deleted = true;
        while(x-1>=0 && y-1>=0 && board[x-1][y-1]==kulka)
        {
            gtk_button_set_image(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(plansza), y-1, x-1)), NULL);
            board[x-1][y-1] = 0;
            x--;
            y--;
        }
        x = a;
        y = b;
        while(x+1<=8 && y+1<=8 && board[x+1][y+1]==kulka)
        {
            gtk_button_set_image(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(plansza), y+1, x+1)), NULL);
            board[x+1][y+1] = 0;
            x++;
            y++;
        }
    }
    x = a;
    y = b;

    //PRAWY SKOS
    licznik = 1;
    while(x-1>=0 && y+1<=8 && board[x-1][y+1]==kulka)
    {
        licznik++;
        x--;
        y++;
    }
    x = a;
    y = b;
    while(x+1<=8 && y-1>=0 && board[x+1][y-1]==kulka)
    {
        licznik++;
        x++;
        y--;
    }
    x = a;
    y = b;
    if(licznik>=5)
    {
        suma+=licznik-1;
        deleted = true;
        while(x-1>=0 && y+1<=8 && board[x-1][y+1]==kulka)
        {
            gtk_button_set_image(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(plansza), y+1, x-1)), NULL);
            board[x-1][y+1] = 0;
            x--;
            y++;
        }
        x = a;
        y = b;
        while(x+1<=8 && y-1>=0 && board[x+1][y-1]==kulka)
        {
            gtk_button_set_image(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(plansza), y-1, x+1)), NULL);
            board[x+1][y-1] = 0;
            x++;
            y--;
        }
    }
    x = a;
    y = b;


    //GLOWNA KULKA
    if(deleted)
    {
        gameOver = false;
        gtk_button_set_image(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(plansza), y, x)), NULL);
        board[x][y] = 0;
        suma++;
    }
    sumapkt += suma;
    gtk_button_set_label(GTK_BUTTON(sumPoints), intToString(sumapkt));
}

void newGame(GtkWidget* nowa)
{
    gameOver = false;
    gtk_label_set_text(GTK_LABEL(przyciskM), "");
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            gtk_button_set_image(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(plansza), j, i)), NULL);
            board[i][j] = 0;
        }
    }
    addBalls();
    putNextBalls();
    sumapkt = 0;
    gtk_button_set_label(GTK_BUTTON(sumPoints), intToString(sumapkt));

    /*for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            g_print("%d ", board[i][j]);
        }
        g_print("\n");
    }
    g_print("\n");*/
}

void addBalls()
{
    p1 = randCell();
    if(p1!=-1)
    {
        gtk_button_set_image(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(plansza), p1%9, p1/9)), putColor(nextB[0]));
        board[p1/9][p1%9] = nextB[0]+1;
    }
    else
    {
        gameOver = true;
        nextBalls();
        return;
    }
    p2 = randCell();
    if(p2!=-1)
    {
        gtk_button_set_image(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(plansza), p2%9, p2/9)), putColor(nextB[1]));
        board[p2/9][p2%9] = nextB[1]+1;
    }
    else
    {
        gameOver = true;
        nextBalls();
        return;
    }
    p3 = randCell();
    if(p3!=-1)
    {
        gtk_button_set_image(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(plansza), p3%9, p3/9)), putColor(nextB[2]));
        board[p3/9][p3%9] = nextB[2]+1;
    }
    else
    {
        gameOver = true;
        nextBalls();
        return;
    }
    if(randCell()==-1)
    {
        gameOver=true;
    }
    nextBalls();
}

int randCell()
{
    int p = rand()%81;
    if(board[p/9][p%9]==0) return p;
    int k=0;
    while(k<81)
    {
        p = (p+1)%81;
        k++;
        if(board[p/9][p%9]==0) return p;
    }
    return -1;
}

GtkWidget* putColor(int los)
{
    GtkWidget* kulka = NULL;
    switch(los)
    {
        case 0:
           kulka = gtk_image_new_from_file("grafika/red.png");
           break;
        case 1:
           kulka = gtk_image_new_from_file("grafika/blue.png");
           break;
        case 2:
           kulka = gtk_image_new_from_file("grafika/purple.png");
           break;
        case 3:
           kulka = gtk_image_new_from_file("grafika/green.png");
           break;
        case 4:
           kulka = gtk_image_new_from_file("grafika/yellow.png");
           break;
        case 5:
           kulka = gtk_image_new_from_file("grafika/orange.png");
           break;
        case 6:
           kulka = gtk_image_new_from_file("grafika/pink.png");
    }
    return kulka;
}

GtkWidget* putColorM(int los)
{
    GtkWidget* kulka = NULL;
    switch(los)
    {
        case 0:
           kulka = gtk_image_new_from_file("grafika/redM.png");
           break;
        case 1:
           kulka = gtk_image_new_from_file("grafika/blueM.png");
           break;
        case 2:
           kulka = gtk_image_new_from_file("grafika/purpleM.png");
           break;
        case 3:
           kulka = gtk_image_new_from_file("grafika/greenM.png");
           break;
        case 4:
           kulka = gtk_image_new_from_file("grafika/yellowM.png");
           break;
        case 5:
           kulka = gtk_image_new_from_file("grafika/orangeM.png");
           break;
        case 6:
           kulka = gtk_image_new_from_file("grafika/pinkM.png");
    }
    return kulka;
}

int colorNum()
{
    return rand()%7;
}

void chooseBall(GtkWidget* button)
{
    if(gameOver)
    {
        gtk_label_set_text(GTK_LABEL(przyciskM), "Koniec gry!");
        return;
    }
    GtkWidget* image = gtk_button_get_image(GTK_BUTTON(button));
    if(image == NULL) return;

    clickedBall = true;

    prevButton = button;
    GValue top = G_VALUE_INIT;
    GValue left = G_VALUE_INIT;
    g_value_init(&top, G_TYPE_INT);
    g_value_init(&left, G_TYPE_INT);
    gtk_container_child_get_property(GTK_CONTAINER(plansza), button, "top-attach", &top);
    gtk_container_child_get_property(GTK_CONTAINER(plansza), button, "left-attach", &left);
    x = g_value_get_int(&top);
    y = g_value_get_int(&left);
    px = x;
    py = y;
}

void moveBall(GtkWidget* button)
{
    if(clickedBall == false) return;
    GtkWidget* image = gtk_button_get_image(GTK_BUTTON(button));
    if(image != NULL) return;

    GValue top = G_VALUE_INIT;
    GValue left = G_VALUE_INIT;
    g_value_init(&top, G_TYPE_INT);
    g_value_init(&left, G_TYPE_INT);
    gtk_container_child_get_property(GTK_CONTAINER(plansza), button, "top-attach", &top);
    gtk_container_child_get_property(GTK_CONTAINER(plansza), button, "left-attach", &left);
    x = g_value_get_int(&top);
    y = g_value_get_int(&left);

    //BFS
    int dest = x*9 + y;
    int start = px*9 + py;

    if(!isPath(board, start, dest))
    {
        gtk_label_set_text(GTK_LABEL(przyciskM), "Niedozwolony ruch!\n");
        return;
    }
    gtk_label_set_text(GTK_LABEL(przyciskM), "");
    int tmp = board[px][py];
    board[px][py] = 0;

    GtkWidget* prevBall = putColor(tmp-1);
    board[x][y] = tmp;

    gtk_button_set_image(GTK_BUTTON(button), prevBall);
    gtk_button_set_image(GTK_BUTTON(prevButton), NULL);
    clickedBall = false;
    movedBall = true;
    deleteCorrectRow(x, y);
    if(!deleted)
    {
        addBalls();
        putNextBalls();
        if(p1 == -1) return;
        if(p2 == -1)
        {
            deleteCorrectRow(p1/9, p1%9);
            return;
        }
        if(p3 == -1)
        {
            deleteCorrectRow(p1/9, p1%9);
            if(board[p2/9][p2%9] != 0) deleteCorrectRow(p2/9, p2%9);
            return;
        }
        deleteCorrectRow(p1/9, p1%9);
        if(board[p2/9][p2%9] != 0) deleteCorrectRow(p2/9, p2%9);
        if(board[p3/9][p3%9] != 0) deleteCorrectRow(p3/9, p3%9);
    }

    /*for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            g_print("%d ", board[i][j]);
        }
        g_print("\n");
    }
    g_print("\n");*/
}

int main (int argc, char* argv[])
{
    srand(time(NULL));
    gtk_init (&argc, &argv);

    GtkWidget* okno;
    GtkWidget* box;
    GtkWidget* przycisk;
    GtkWidget* kontrolki;
    GtkWidget* sumaPkt;
    GtkWidget* wyjdzzGry;
    GtkWidget* nowaGra;
    GtkWidget* zapiszGre;
    GtkWidget* wczytajGre;

    okno = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(okno), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(okno), "GRA KULKI");
    gtk_window_set_default_size(GTK_WINDOW(okno), 1000, 1080); //Dopasuj rozmiar na koniec
    gtk_window_set_resizable(GTK_WINDOW(okno), FALSE);
    gtk_container_set_border_width(GTK_CONTAINER(okno), 50);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);

    kontrolki = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);

    kolejneKulki = gtk_grid_new();

    gtk_grid_set_row_spacing(GTK_GRID(kolejneKulki), 0);
    gtk_grid_set_row_homogeneous(GTK_GRID(kolejneKulki), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(kolejneKulki), 0);
    gtk_grid_set_column_homogeneous(GTK_GRID(kolejneKulki), FALSE);

    gtk_box_pack_start(GTK_BOX(box), kontrolki, TRUE, TRUE, 20);

    sumaPkt = gtk_label_new("Suma punktów:");

    sumPoints = gtk_button_new_with_label("0");
    wyjdzzGry = gtk_button_new_with_label("Wyjdź z gry");
    nowaGra = gtk_button_new_with_label("Nowa gra");
    wczytajGre = gtk_button_new_with_label("Wczytaj grę");
    zapiszGre = gtk_button_new_with_label("Zapisz grę");

    gtk_box_pack_start(GTK_BOX(kontrolki), sumaPkt, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(kontrolki), sumPoints, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(kontrolki), kolejneKulki, TRUE, TRUE, 50);
    gtk_box_pack_start(GTK_BOX(kontrolki), nowaGra, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(kontrolki), zapiszGre, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(kontrolki), wczytajGre, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(kontrolki), wyjdzzGry, TRUE, TRUE, 0);


    plansza = gtk_grid_new();

    gtk_grid_set_row_spacing(GTK_GRID(plansza), 0);
    gtk_grid_set_row_homogeneous(GTK_GRID(plansza), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(plansza), 0);
    gtk_grid_set_column_homogeneous(GTK_GRID(plansza), TRUE);


    gtk_box_pack_start(GTK_BOX(box), plansza, TRUE, TRUE, 20);
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            przycisk = gtk_button_new();
            g_signal_connect(G_OBJECT(przycisk), "clicked", G_CALLBACK(chooseBall), NULL);
            g_signal_connect(G_OBJECT(przycisk), "clicked", G_CALLBACK(moveBall), NULL);
            gtk_grid_attach(GTK_GRID(plansza), przycisk, j, i, 1, 1);
        }
    }
    nextBalls();
    addBalls();

    nextBalls();
    for(int i=0; i<3; i++)
    {
        przyciskM = gtk_button_new();
        gtk_button_set_image(GTK_BUTTON(przyciskM), putColorM(nextB[i]));
        gtk_grid_attach(GTK_GRID(kolejneKulki), przyciskM, i, 0, 1, 1);
    }
    przyciskM = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(kolejneKulki), przyciskM, 0, 1, 3, 1);

    gtk_container_add(GTK_CONTAINER(okno), box);

    g_signal_connect(G_OBJECT(okno), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(wyjdzzGry), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(nowaGra), "clicked", G_CALLBACK(newGame), NULL);
    g_signal_connect(G_OBJECT(zapiszGre), "clicked", G_CALLBACK(saveGame), NULL);
    g_signal_connect(G_OBJECT(wczytajGre), "clicked", G_CALLBACK(loadGame), NULL);

    gtk_widget_show_all(okno);

    gtk_main();

	return 0;
}
