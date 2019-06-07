function gerarV(V,n)
       for i in 1:n
       a = rand(1:2)
       if a == 1 V[i] = 1
       end
       if a == 2 V[i] = -1
       end
       end
       end

function elemento(i,j)
       if i == j return 4
       end
       if abs(i-j) == 1 return -1
       end
       if abs(i-j)>1 return 0
       end
       end

function calcularB(V,B,n)
       for i in 1:n
       B[i] = 0
       for j in 1:n
       B[i] = B[i] + (elemento(i,j)*V[j])
       end
       end
       end

function residuo(result,B,resid,n)
       for i in 1:n
       resid[i] = B[i]
       for j in 1:n
       resid[i] = resid[i] - (elemento(i,j)*result[j])
       end
       end
       end

 function normaLinha(resid,n)
       prov_max = 0.0
       for i in 1:n
       resid[i] = abs(resid[i])
       end
       for j in 1:n
       if resid[j]>prov_max 
            prov_max = resid[j]
       end
       end
       return prov_max
       end

function comparar(result,V,n)
       for i in 1:n
       if result[i] != V[i] return false
            else return true
       end
       end
       end

function jacobi(B,V,s_inicial,n,it,armazenamento)
       for m in 1:n
       s_inicial[m] = 0.0
       end
       soma = 0.0
       result = Array{Float64}(undef,n)
       resid = Array{Float64}(undef,n)
       for k in 1:it
       for i in 1:n
       for j in 1:n
       if j!=i soma += (elemento(i,j)*s_inicial[j])
       end
       end
       result[i] = (B[i] - soma)/elemento(i,i)
       soma = 0.0
       end
       for y in 1:n
       s_inicial[y] = result[y]
       end
       residuo(result,B,resid,n)
       armazenamento[k] = normaLinha(resid,n)
       end
       if (comparar(result,V,n)) println("O resultado confere com o esperado.")
        else println("O resultado não confere com o esperado.")
       end
       println("Vetor resultado encontrado:", result)
       println("Vetor resultado real:      ", V)
end

function gseidel(B,V,s_inicial,n,it,armazenamento)
    for m in 1:n
    s_inicial[m] = 0.0
    end
    soma = 0.0
    result = Array{Float64}(undef,n)
    resid = Array{Float64}(undef,n)
    for k in 1:it
    for i in 1:n
    soma = 0.0
    for j in 1:(i-1)
    soma += (elemento(i,j)*result[j])
    end
    for l in i+1:n
    soma+= (elemento(i,l)*s_inicial[l])
    end
    result[i] = (B[i] - soma)/elemento(i,i)
    soma = 0.0
    end
    for y in 1:n
    s_inicial[y] = result[y]
    end
    residuo(result,B,resid,n)
    armazenamento[k] = normaLinha(resid,n)
    end
    if (comparar(result,V,n)) println("O resultado confere com o esperado.")
    else println("O resultado não confere com o esperado.")
    end
end
    
    
    

n = 100
it = 100
B = Array{Float64}(undef,n)
V = Array{Float64}(undef,n)
s_inicial = Array{Float64}(undef,n)
resid = Array{Float64}(undef,n)
armazenamento = Array{Float64}(undef,it)


gerarV(V,n)
calcularB(V,B,n)
gseidel(B,V,s_inicial,n,it,armazenamento)
armazenamento
