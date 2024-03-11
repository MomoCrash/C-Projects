void AskInt (const char* text, int* value) {
    printf(text, "\n");
    scanf("%d", value);
}

int Replay () {
    if(Replay == 0) {
        main();
    }
    else {
        return 1;
    }
}