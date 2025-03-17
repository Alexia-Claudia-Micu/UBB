function rez=ex1_lab3_forward(x,f)
    n=length(x);
    A=zeros(n);
    A(:,1)=f;
    for(j = 2:n)
        for(i=1:n-j+1)
            A(i,j)=A(i+1,j-1)-A(i,j-1);
        end
    end
    rez = A
end

function rez=ex2_lab3_backward(x,f)
    n=length(x);
    A=zeros(n);
    A(:,1)=f;
    for(j = 2:n)
        for(i=j:n)
            A(i,j)=A(i,j-1)-A(i-1,j-1);
        end
    end
    rez = A
end


function rez=ex3_lab3_dividedDiff_simpleNodes(x,f)
    n=length(x);
    A=zeros(n);
    A(:,1)=f;
    for(j = 2:n)
        for(i=1:n-j+1)
            A(i,j)=(A(i+1,j-1)-A(i,j-1))./(x(i+j-1)-x(i))
        end
    end
    rez = A
end


function rez=ex4_lab3_dividedDiff(x,f,fp)
    n=length(x);
    z=zeros(1,2*n);
    for(i=1:n)
        z(2*i -1) = x(i);
        z(2*i) = x(i);
    end

    m=length(z);
    A=zeros(m);
    %fz=1./(1+z);

    fz = zeros(1,m);
    for(i=1:n)
        fz(2*i-1)=f(i);
        fz(2*i)=f(i);
    end

    A(:,1) = fz;
    A(1:2:m,2)=fp;

    for(i=2:2:m-1)
        A(i,2) = (A(i+1,1)-A(i,1))/(z(i+1)-z(i));
    end

    for(j = 3:m)
        for(i=1:m-j+1)
            A(i,j)=(A(i+1,j-1)-A(i,j-1))./(z(i+j-1)-z(i))
        end
    end

    rez = A;
end

x=[0,1,2]; % linspace(1,2,11) for 11 equidistant in [1,2]
f = 1./(x+1);
fp = -1./(x+1).^2;

rez = ex4_lab3_dividedDiff(x,f,fp)