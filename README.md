# Simulador de Disco Magnético Rígido

Características do disco: 

* Trilhas por cilindro: 5
* Setores por trilha: 60
* Trilhas por superfície: 10
* Tamanho do setor: 512 bytes
* Tamanho do cluster: 4 setores
* Tempo médio de seek: 4 ms
* Tempo mínimo de seek: 1ms
* Tempo media de latência: 6ms
* Tempo de transferência: 12ms/trilha

* Sistema utilizado:  
    Mac Os X El Captain 64-bit  

## Rodar simulador:
    sudo make : Gera arquivos para executar o simulador
    sudo make clean : Limpa arquivos objetos gerados pelo sudo make
    ./my_drive : Executa o simulador