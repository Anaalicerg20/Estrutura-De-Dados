#include "../include/Sistema.h"
#include <iostream>
#include <string>

// construtor
Sistema::Sistema()
{
    proximoIdUsuario = 0;
    proximoIdProduto = 0;
    proximoIdCompra = 0;
    proximoIdReposicao = 0;
}

//cadastros
void Sistema::cadastrarUsuario(const std::string& nome, int idade, const std::string& cidade, const std::string& estado, const std::string& nacionalidade){
    // gera ID automático
    int id = proximoIdUsuario;

    // cria usuário
    Usuario novoUsuario = Usuario(id, nome, idade, cidade, estado, nacionalidade);

    // armazena usuário no vetor de usuarios e atualiza o histórico
    usuarios.adicionar(novoUsuario);
    historicoUsuarios.adicionar(Vetor<Historico>()); 

    // atualiza índices invertidos (atributo -> id)
    indiceUsuarioId.inserir(std::to_string(id), id);
    indiceUsuarioNome.inserir(nome, id);
    indiceUsuarioIdade.inserir(std::to_string(idade), id);// string(idade) -> id 
    indiceUsuarioCidade.inserir(cidade, id);
    indiceUsuarioEstado.inserir(estado, id);
    indiceUsuarioNacionalidade.inserir(nacionalidade, id);

    // saída
    std::cout << "U " << id << std::endl;

    // próximo ID disponível
    proximoIdUsuario++;
}

void Sistema::cadastrarProduto(const std::string& nome, double preco, int qtd, const std::string& categoria, const std::string& marca, const std::string& condicao){
    // gera ID automático
    int id = proximoIdProduto;

    // cria produto
    Produto novoProduto = Produto(id, nome, preco, qtd, categoria, marca, condicao);

    // armazena produto no vetor de produtos e atualiza o historico
    produtos.adicionar(novoProduto);
    historicoProdutos.adicionar(Vetor<Historico>());

    // atualiza índices invertidos (atributo -> id)
    indiceProdutoId.inserir(std::to_string(id), id);
    indiceProdutoNome.inserir(nome, id);
    indiceProdutoCategoria.inserir(categoria, id);
    indiceProdutoMarca.inserir(marca, id);
    indiceProdutoCondicao.inserir(condicao, id);

    // saída
    std::cout << "P " << id << std::endl;

    // próximo ID disponível
    proximoIdProduto++;
}

//funções auxiliares: atualizar o histórico
void Sistema::atualizarHistoricoUsuario(int idUsuario, int idProduto,int quantidade){
    Vetor<Historico>& historico = historicoUsuarios[idUsuario];

    for(int i = 0; i < historico.getTamanho(); i++)
    {
        if(historico[i].getId() == idProduto)
        {
            historico[i].adicionarQuantidade(quantidade);
            return;
        }
    }

    historico.adicionar(
        Historico(idProduto, quantidade)
    );
}

void Sistema::atualizarHistoricoProduto(int idProduto,int idUsuario,int quantidade){
    Vetor<Historico>& historico = historicoProdutos[idProduto];

    for(int i = 0; i < historico.getTamanho(); i++)
    {
        if(historico[i].getId() == idUsuario)
        {
            historico[i].adicionarQuantidade(quantidade);
            return;
        }
    }

    historico.adicionar(
        Historico(idUsuario, quantidade)
    );
}



//operações
void Sistema::processarReposicao(std::stringstream& ss){
    // lê timestamp da reposição
    int timestamp;
    ss >> timestamp;

    // vetores que armazenam os produtos da reposição (temporários)
    Vetor<int> ids_produtos;
    Vetor<int> qtd_produtos;

    int idProduto;
    int quantidade;

    // lê todos os pares <id_produto> <qtd>
    while (ss >> idProduto >> quantidade)
    {
        ids_produtos.adicionar(idProduto);
        qtd_produtos.adicionar(quantidade);

        produtos[idProduto].aumentarQtd(quantidade); // atualiza estoque do produto
    }

    int idReposicao = proximoIdReposicao; // gera ID automático

    Reposicao novaReposicao = Reposicao(idReposicao, timestamp, ids_produtos, qtd_produtos); //cria

    reposicoes.adicionar(novaReposicao); //add no vetor de resposicao

    // atualiza índices invertidos
    indiceReposicaoId.inserir(std::to_string(idReposicao), idReposicao); // id da reposição -> id da reposição
    indiceReposicaoTimestamp.inserir(std::to_string(timestamp), idReposicao);  // timestamp -> id da reposição
    for (int i = 0; i < ids_produtos.getTamanho(); i++)
    {
        indiceReposicaoProduto.inserir(std::to_string(ids_produtos[i]),idReposicao); // id_produto -> id da reposição
    }

    std::cout << "R " << idReposicao << std::endl; //saída

    proximoIdReposicao++; //prox ID
}

void Sistema::processarCompra(std::stringstream& ss){
    // lê timestamp e usuário
    int timestamp;
    int idUsuario;

    ss >> timestamp >> idUsuario;

    // vetores temporários da compra
    Vetor<int> ids_produtos;
    Vetor<int> qtd_produtos;

    int idProduto;
    int quantidade;

    // lê todos os pares <id_produto> <qtd>
    while (ss >> idProduto >> quantidade)
    {
        ids_produtos.adicionar(idProduto);
        qtd_produtos.adicionar(quantidade);
    }

    // verifica se existe estoque suficiente para TODOS os produtos
    bool compraValida = true;

    for (int i = 0; i < ids_produtos.getTamanho(); i++)
    {
        int produto = ids_produtos[i];
        int qtdDesejada = qtd_produtos[i];

        if (produtos[produto].getQtd() < qtdDesejada)
        {
            compraValida = false;
            break;
        }
    }

    // compra inválida
    if (!compraValida)
    {
        std::cout << "C INV" << std::endl;
        return;
    }

    // atualiza estoque dos produtos
    for (int i = 0; i < ids_produtos.getTamanho(); i++)
    {
        produtos[ids_produtos[i]].diminuirQtd(qtd_produtos[i]);
    }

    int idCompra = proximoIdCompra; // gera ID automático
    Compra novaCompra = Compra (idCompra,timestamp,idUsuario,ids_produtos,qtd_produtos);   // cria compra
    compras.adicionar(novaCompra); // adiciona ao vetor de compras

    //atualização dos históricos
    for(int i = 0; i < ids_produtos.getTamanho(); i++){
            atualizarHistoricoUsuario(idUsuario, ids_produtos[i], qtd_produtos[i]);
            atualizarHistoricoProduto(ids_produtos[i], idUsuario, qtd_produtos[i]);
        }

    // atualiza índices invertidos
    indiceCompraId.inserir(std::to_string(idCompra),idCompra);
    indiceCompraTimestamp.inserir(std::to_string(timestamp), idCompra); // timestamp -> id da compra
    indiceCompraUsuario.inserir(std::to_string(idUsuario), idCompra); // id_usuario -> id da compra
    for (int i = 0; i < ids_produtos.getTamanho(); i++)
    {
        indiceCompraProduto.inserir(std::to_string(ids_produtos[i]), idCompra);     // id_produto -> id da compra
    }

    // saída
    std::cout << "C " << idCompra << std::endl;

    // próximo ID disponível
    proximoIdCompra++;
}

//intersecção entre conjuntos(vetor em ordem crescente de id): auxiliar para consultas
Vetor<int> Sistema::intersecao(const Vetor<int>& a, const Vetor<int>& b){
    Vetor<int> resultado;

    int i = 0;
    int j = 0;

    while (i < a.getTamanho() && j < b.getTamanho())
    {
        int valorA = a[i];
        int valorB = b[j];

        if (valorA == valorB)
        {
            resultado.adicionar(valorA);

            i++;
            j++;
        }
        else if (valorA < valorB)
        {
            i++;
        }
        else
        {
            j++;
        }
    }

    return resultado;
}

//consultas
void Sistema::consultarUsuarios(std::stringstream& ss)
{
    std::string atributo;
    std::string valor;

    Vetor<int> resultado;
    bool primeiroFiltro = true;

    while (ss >> atributo >> valor)
    {
        const Vetor<int>* ids = nullptr;

        // escolhe o índice correto
        if (atributo == "id"){
            ids = indiceUsuarioId.buscar(valor);
        }
        else if (atributo == "nome"){
            ids = indiceUsuarioNome.buscar(valor);
        }
        else if (atributo == "idade"){
            ids = indiceUsuarioIdade.buscar(valor);
        }
        else if (atributo == "cidade"){
            ids = indiceUsuarioCidade.buscar(valor);
        }
        else if (atributo == "estado"){
            ids = indiceUsuarioEstado.buscar(valor);
        }
        else if (atributo == "nacionalidade"){
            ids = indiceUsuarioNacionalidade.buscar(valor);
        }

        // se não existe nenhum usuário com esse filtro → resultado vazio
        if (ids == nullptr){
            resultado = Vetor<int>();
            break;
        }

        if (primeiroFiltro){ //inicializa resultado

            resultado = *ids;
            primeiroFiltro = false;
        }
        else{
            resultado = intersecao(resultado, *ids); //faz a inetersecção entre os vetores
        }

        if (resultado.getTamanho() == 0) // se ja está vazio, para
            break;
    }

    // sem resultados
    if (resultado.getTamanho() == 0){

        std::cout << "LU VAZIO" << std::endl;
        return;
    }

    // imprime resultados
    for (int i = 0; i < resultado.getTamanho(); i++){

        int id = resultado[i];
        Usuario& u = usuarios[id];

        std::cout << "LU resultado_" << (i + 1) << " usuario " << u.getId() << " " << u.getNome() << " " << u.getIdade() << " " << u.getCidade() << " " << u.getEstado() << " " << u.getNacionalidade() << std::endl;

        // imprime histórico (produtos comprados pelo usuário)
        Vetor<Historico>& hist = historicoUsuarios[id];

        if (!hist.estaVazio())
        {
            // Ordenação do histórico por ID do produto (Selection Sort)
            for (int a = 0; a < hist.getTamanho(); a++) {
                int minIdx = a;
                for (int b = a + 1; b < hist.getTamanho(); b++) {
                    if (hist[b].getId() < hist[minIdx].getId()) {
                        minIdx = b;
                    }
                }
                if (minIdx != a) {
                    // Troca os objetos Historico de posição
                    Historico temp = hist[a];
                    hist[a] = hist[minIdx];
                    hist[minIdx] = temp;
                }
            }
            for (int j = 0; j < hist.getTamanho(); j++)
            {
                if (j > 0) std::cout << " ";
                std::cout << "produto_" << (j + 1) << " " << hist[j].getId() << " " << hist[j].getQuantidade();
            }
            std::cout << std::endl;
        }
    }
}

void Sistema::consultarProdutos(std::stringstream& ss){
    std::string atributo;
    std::string valor;

    Vetor<int> resultado;
    bool primeiroFiltro = true;

    while (ss >> atributo >> valor){
        const Vetor<int>* ids = nullptr;

        // escolhe o índice correto de produtos
        if (atributo == "id"){
            ids = indiceProdutoId.buscar(valor);
        }
        else if (atributo == "nome"){
            ids = indiceProdutoNome.buscar(valor);
        }
        else if (atributo == "categoria"){
            ids = indiceProdutoCategoria.buscar(valor);
        }
        else if (atributo == "marca"){
            ids = indiceProdutoMarca.buscar(valor);
        }
        else if (atributo == "condicao"){
            ids = indiceProdutoCondicao.buscar(valor);
        }

        // se não existe produto com esse filtro → vazio
        if (ids == nullptr){
            resultado = Vetor<int>();
            break;
        }

        if (primeiroFiltro){
            resultado = *ids;
            primeiroFiltro = false;
        }
        else{
            resultado = intersecao(resultado, *ids); 
        }

        if (resultado.getTamanho() == 0)
            break;
    }

    // sem resultados
    if (resultado.getTamanho() == 0){
        std::cout << "LP VAZIO" << std::endl;
        return;
    }

    // imprime resultados
    for (int i = 0; i < resultado.getTamanho(); i++){
        int id = resultado[i];
        Produto& p = produtos[id];

        std::cout << "LP resultado_" << (i + 1) << " produto " << p.getId() << " " << p.getNome() << " ";

        // garante preço com 2 casas decimais
        std::cout.setf(std::ios::fixed);
        std::cout.precision(2);
        std::cout << p.getPreco() << " ";

        std::cout << p.getQtd() << " " << p.getCategoria() << " " << p.getMarca() << " " << p.getCondicao() << std::endl;

        // histórico: usuários que compraram o produto
        Vetor<Historico>& hist = historicoProdutos[id];

        if (!hist.estaVazio())
        {
            // Ordenação do histórico por ID do usuário (Selection Sort - idêntico ao outro)
            for (int a = 0; a < hist.getTamanho(); a++) {
                int minIdx = a;
                for (int b = a + 1; b < hist.getTamanho(); b++) {
                    if (hist[b].getId() < hist[minIdx].getId()) {
                        minIdx = b;
                    }
                }
                if (minIdx != a) {
                    // Troca os objetos Historico de posição
                    Historico temp = hist[a];
                    hist[a] = hist[minIdx];
                    hist[minIdx] = temp;
                }
            }

            for (int j = 0; j < hist.getTamanho(); j++)
            {
                if (j > 0) std::cout << " ";

                std::cout << "usuario_" << (j + 1) << " "<< hist[j].getId() << " "<< hist[j].getQuantidade();
            }
            std::cout << std::endl;
        }
    }
}

void Sistema::consultarCompras(std::stringstream& ss){
    std::string atributo;
    std::string valor;

    Vetor<int> resultado;
    bool primeiroFiltro = true;

    while (ss >> atributo >> valor){
        const Vetor<int>* ids = nullptr;

        // seleção do índice correto
        if (atributo == "id"){
            ids = indiceCompraId.buscar(valor);
        }
        else if (atributo == "timestamp"){
            ids = indiceCompraTimestamp.buscar(valor);
        }
        else if (atributo == "id_usuario"){
            ids = indiceCompraUsuario.buscar(valor);
        }
        else if (atributo == "id_produto"){
            ids = indiceCompraProduto.buscar(valor);
        }

        // nenhum resultado para esse filtro
        if (ids == nullptr){
            resultado = Vetor<int>();
            break;
        }

        if (primeiroFiltro){
            resultado = *ids;
            primeiroFiltro = false;
        }
        else{
            resultado = intersecao(resultado, *ids);
        }

        if (resultado.getTamanho() == 0)
            break;
    }

    // nenhum resultado final
    if (resultado.getTamanho() == 0){
        std::cout << "LC VAZIO" << std::endl;
        return;
    }

    // imprime resultados
    for (int i = 0; i < resultado.getTamanho(); i++){
        int idCompra = resultado[i];
        Compra& c = compras[idCompra];

        std::cout << "LC resultado_" << (i + 1) << " compra " << c.getId() << " timestamp " << c.getTimestamp() << " usuario " << c.getIdUsuario() << std::endl;

        // acesso aos produtos da compra
        Vetor<int> idsProd = c.getIdsProdutos();
        Vetor<int> qtdProd = c.getQtdProdutos();

        // imprime produtos em ordem crescente de id, Oordenação por selection sort
        for (int a = 0; a < idsProd.getTamanho(); a++){
            int minIdx = a;
            for (int b = a + 1; b < idsProd.getTamanho(); b++){
                if (idsProd[b] < idsProd[minIdx])
                    minIdx = b;
            }

            if (minIdx != a){
                int tmpId = idsProd[a];
                int tmpQtd = qtdProd[a];

                idsProd[a] = idsProd[minIdx];
                qtdProd[a] = qtdProd[minIdx];

                idsProd[minIdx] = tmpId;
                qtdProd[minIdx] = tmpQtd;
            }
        }

        for (int j = 0; j < idsProd.getTamanho(); j++)
        {
            if (j > 0) std::cout << " ";

            std::cout << "produto_" << (j + 1) << " " << idsProd[j] << " " << qtdProd[j];
        }
        std::cout << std::endl;
    }
}

void Sistema::consultarReposicoes(std::stringstream& ss){
    std::string atributo, valor;

    Vetor<int> resultado;
    bool primeiroFiltro = true;

    while (ss >> atributo >> valor){
        const Vetor<int>* ids = nullptr;

        if (atributo == "id"){
            ids = indiceReposicaoId.buscar(valor);
        }
        else if (atributo == "timestamp"){
            ids = indiceReposicaoTimestamp.buscar(valor);
        }
        else if (atributo == "id_produto"){
            ids = indiceReposicaoProduto.buscar(valor);
        }

        if (ids == nullptr){
            resultado = Vetor<int>();
            break;
        }

        if (primeiroFiltro){
            resultado = *ids;
            primeiroFiltro = false;
        }
        else{
            resultado = intersecao(resultado, *ids);
        }

        if (resultado.getTamanho() == 0)
            break;
    }

    if (resultado.getTamanho() == 0)
    {
        std::cout << "LR VAZIO" << std::endl;
        return;
    }

    for (int i = 0; i < resultado.getTamanho(); i++)
    {
        int idRep = resultado[i];
        Reposicao& r = reposicoes[idRep];

        std::cout << "LR resultado_" << (i + 1) << " reposicao " << r.getId() << " timestamp " << r.getTimestamp() << std::endl;

        Vetor<int> idsProd = r.getIdsProdutos();
        Vetor<int> qtdProd = r.getQtdProdutos();

        // ordenação por id do produto
        for (int a = 0; a < idsProd.getTamanho(); a++)
        {
            int minIdx = a;

            for (int b = a + 1; b < idsProd.getTamanho(); b++)
            {
                if (idsProd[b] < idsProd[minIdx])
                    minIdx = b;
            }

            if (minIdx != a)
            {
                int tmpId = idsProd[a];
                int tmpQtd = qtdProd[a];

                idsProd[a] = idsProd[minIdx];
                qtdProd[a] = qtdProd[minIdx];

                idsProd[minIdx] = tmpId;
                qtdProd[minIdx] = tmpQtd;
            }
        }

        for (int j = 0; j < idsProd.getTamanho(); j++){
            if (j > 0) std::cout << " ";

            std::cout << "produto_" << (j + 1) << " "<< idsProd[j] << " " << qtdProd[j];
        }

        std::cout << std::endl;
    }
}