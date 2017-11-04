import java.io.File;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.PrintWriter;
import java.io.IOException;
import java.lang.Math;
import java.util.ArrayList;
import java.util.Collections;

class kaiseki01
{
    public static void main(String args[])
    {
	double Rad=40000.0/(199*8),delta=0.01*Rad,a=399.0*Rad/200,Ct=-0.25/(Rad*Rad),Cl=1.0/(796*Rad*Rad),dd=Math.PI/4.0,lambda,prlam,prlamtmp;
	//aは格子間距離, deltaはoverlapの間隔
	ArrayList<Double> Lam = new ArrayList<Double>();
	
	try{
	    File file = new File("hey.txt");
	    file.createNewFile();
	    
	    if(checkBeforeWritefile(file))
		{
		    PrintWriter pw =new PrintWriter(new FileWriter(file));

		    for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
			    {
				lambda=2*(Ct*(Math.cos(-Math.PI+dd*i)-1)+Cl*(Math.cos(-Math.PI+dd*j)-1));
				Lam.add(new Double(lambda));

				pw.println((-Math.PI+dd*i)+" "+(-Math.PI+dd*j)+" "+lambda);
				if(Math.abs(lambda)<0.00000000001)
				    System.out.println((-Math.PI+dd*i)+" "+(-Math.PI+dd*j)+" "+lambda);
			    }

		    Collections.sort(Lam);
		    Collections.reverse(Lam);
		    pw.println("\n--------------------------");

		    prlamtmp=prlam=Lam.get(0);
		    pw.println("* "+prlam);
		    for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
			    {
				if(i==0 && j==0)
				    ;
				else
				    {
				prlam=Lam.get(8*i+j);
				if(Math.abs(prlam-prlamtmp)>0.000000001)
				    pw.print("* ");
				prlamtmp=prlam;
				pw.println(prlam);
				    }
			    }

		    pw.close();	    
		}
	    
	    else
		System.out.println("Cannot write your file><");
	}
	
	catch(IOException e)
	    {
		System.out.println(e);
	    }
    }

    private static boolean checkBeforeWritefile(File file)
    {
	if(file.exists())
	    {
		if(file.isFile() && file.canWrite())
		    {
			return true;
		    }
	    }
	return false;
    }
}

