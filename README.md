# Projeto de TCC grupo .PNG,the boys who are stick in the cat


# Como usar Bitbucket:
[Pode ser meio zuado de usar isso, mas de vdd, pode ajudar mt. Ele irá controlar todo nosso código, se dar algum problema sempre seŕa possível recuperar facilmente. Se duas pessoas editarem um memso codigo ao mesmo tempo, nem precisam trocar ideias, o git da conta de gerenciar e ver o que cada um fez e mesclar o código. O esforço vale a pena]

Baixe e instale o Git here: http://git-scm.com/

### Para baixar o fonte faça(somente na primeira vez que for utilizar):
Abra o Prompt de comando do Git(sei lá como é o nome no Win, linux é só digitar git)
Vá para a pasta que quer salvar o prj
digite:
    
    git clone https://SeuNomeDeUsuario@bitbucket.org/aron_bordin/robo-tcc.git

não esqueça de colocar seu nome de usuário do bitbucket no comando acima. Ele irá pedir senha, confirme para baixar.

Ok, o código esta no seu PC.

*** Para manter as configurações do repositório remoto, digite:

    
    git remote add origin https://NomeDeUsuario@bitbucket.org/aron_bordin/robo-tcc.git

** [Importante!!] Atualizar seus fontes
Sempre que você for fazer algo no seu projeto, atualize seus fontes para não pegar código antigo sem perceber. Para isso, sempre antes de iniciar uma modificação digite:

    git pull origin master

Esse comando irá atualizar seus fontes.

** [Tbm importante!!] Atualizar fontes servidor
Sempre que terminar alguma modificação(n faça isso a cada save, espere grandes modificações, ou coisas importantes), você precisa enviar o que foi modificado para o server, então digite:

    git add .

Irá adicionar todos os arquivos da sua pasta para o servidor

    git commit -am "Mensagem explicando o que voce fez"

    git push origin master

O commit salva suas mudanças e coloca uma msg informando o q vc fez. Tente sempre explicar com poucas palavras e claramente o q vc fez!!
O git push faz o upload dos fontes.


## 1. Tema do Projeto:


O projeto tem como objetivo proporcionar à FEB e ao CTI pesquisas nas áreas de robótica com o microcontrolador Arduino e análise de imagens com Android.

 
## 2. Situação Problema:


     A situação proposta se caracteriza por simular um ambiente de desastre em mundo real onde o resgate de vítimas precisa ser feito por robôs. Portanto será criada uma situação fictícia, onde teria ocorrido um desastre em que humanos não seriam capazes de realizar os resgates, que terá de ser feito por robôs sem a interferência humana.
A simulação apresentará:

    Terrenos hostis, para testar a agilidade do robô (redutores de velocidade);
    Áreas onde não há trilha reconhecida;
    Obstáculos para o robô desviar;
    Montanhas representadas por rampas;
    Capacidade do robô de carregar uma vítima (lata de refrigerante);
    Uma área segura(ponto de evacuação).

 
## 3. Sistema Proposto (Solução do Problema):


   A ideia do sistema é podermos montar um “protótipo” de um robô capaz de passar por condições físicas desfavoráveis e capaz de resgatar uma vítima e levá-la até um ponto seguro utilizando uma garra robótica, também haverá a montagem de uma pista, que apresentará obstáculos, rampas e linhas por onde o robô se guiará, com o objetivo de simular o cenário que o robô enfrentará.

     Utilizando o microcontrolador Arduino, o grupo trabalhará com o uso de smartphones com sistema Android para a recepção de imagens e possível controle do robô. Também para a simulação, pretendemos utilizar a realidade aumentada como um extra, de modo a termos uma visão mais real do possível cenário que o robô enfrentará.
O sistema funcionará da seguinte forma: o robô apresentará sensores na parte superior, para identificar objetos, seja ele um obstáculo ou o objeto a ser salvo, e na parte inferior, para que guie o robô através das linhas que serão
colocadas na pista. Então, utilizando o Arduino, haverá o tratamento das informações que serão captadas pelos sensores e então será feita uma saída, tanto controlar a garra como os motores. Então, a partir do uso do smartphone,
poderemos ser capazes de controlar o robô e com câmeras instaladas na estrutura poderemos ver onde o robô se encontra.
O robô será projetado pra percorrer uma arena com obstáculos preestabelecidos. Esta arena será baseada na utilizada pela RoboCup Federation®, que deve ser construída em madeira e ter três salas, sendo que duas dessas salas estão num primeiro nível (nível do solo ou térreo) e a terceira sala em um nível mais elevado (primeiro andar ou segundo nível), com rampa de acesso ligando a segunda à terceira sala.

### Piso:

     O piso das salas será uma superfície branca lisa. Este piso representa a área de desastre. Sobre ele haverá:

    linhas pretas para guiarem o robô;
    detritos (obstáculos) típicos do desastre que podem danificar ou impedir o avanço dos robôs;
    Gap’s que simulam falhas no caminho do robô (falhas nas linhas pretas);
    redutores de velocidade que simulam terrenos hostis; 
    a vítima do desastre que precisa ser resgatada;
    uma área, na terceira sala, que indica o ponto de evacuação.

### Linhas:

     As linhas existirão em toda a arena, com exceção da terceira sala, e serão feitas utilizando fita isolante convencional de cor preta, lisa, sem texturas ou marcações. As linhas serão dispostas no chão das salas e da rampa em um trajeto não conhecido. As linhas representam uma passagem segura, conhecida antes do desastre e que pode estar obstruída por obstáculos ou ter redutores de velocidade.
A proposta do projeto é desenvolver um robô que utilize o celular como inteligência e que consiga percorrer arenas baseadas na explicada brevemente acima.
