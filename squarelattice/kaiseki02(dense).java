import java.io.File;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.PrintWriter;
import java.io.IOException;
import java.lang.Math;
import java.util.ArrayList;
import java.util.Collections;

class kaiseki02
{
    public static void main(String args[])
    {
	final int N=65536,sqrtN=256,sqrtNper2=128;
	final double Lengx=400,Lengy=0.5*400*Math.sqrt(3.0);
	double Rad=(Lengx*100)/(sqrtN*199),delta=0.01*Rad,sgm=2*Rad,r=0.01*199*Rad,eps=1.0,DthetaX=2.0*Math.PI/Lengx,DthetaY=4.0*Math.PI/(Lengx*Math.sqrt(3.0));//delta=0.01*Radで計算.
	double ssr=sgm*sgm*r,alp,bet,gam,s=3*eps*(2*r-sgm)/ssr,p,q,lambda,prlam,prlamtmp,Kx,Ky,cum=1.0,dcum=1.0/(2*N-2),phi;
	ArrayList<Double> Lam = new ArrayList<Double>();
	
	try{
	    File file = new File("hey1.txt");
	    File file2 = new File("hey2.txt");
	    file.createNewFile();
	    file2.createNewFile();
	    
	    if(checkBeforeWritefile(file) && checkBeforeWritefile(file2)) {

		PrintWriter pw =new PrintWriter(new FileWriter(file));
		PrintWriter pw2=new PrintWriter(new FileWriter(file2));
		for(int i=0;i<sqrtN;i++)
		    for(int j=0;j<sqrtN;j++) {
			Kx=DthetaX*(i-sqrtNper2);
			Ky=DthetaY*(j-sqrtNper2);
			//Ky=(DthetaY*(4*(i-sqrtNper2)-Math.sqrt(3)*(j-sqrtNper2)));
			alp=(2*eps*Math.cos(r*Kx))/(sgm*sgm);//
			bet=(eps*Math.cos(0.5*r*Kx)*Math.cos(0.5*Math.sqrt(3)*r*Ky))/ssr;//
			gam=-Math.sqrt(3)*eps*Math.sin(0.5*r*Kx)*Math.sin(0.5*Math.sqrt(3)*r*Ky)/ssr;//
			p=alp-bet*(3*sgm-4*r)-s;//
			q=-alp*((sgm-r)/r)-bet*(sgm-4*r)-s;//

			//plus ver
			lambda=-0.5*(p+q)+Math.sqrt(0.25*(p+q)*(p+q)-p*q+gam*gam);
			Lam.add(new Double(lambda));
			pw.println(Kx+" "+Ky+" "+lambda+" "+Math.sqrt(lambda));
			if(Math.abs(lambda)<0.00000000001)
			    System.out.println(Kx+" "+Ky+" "+lambda);
			//minus ver
			lambda=-0.5*(p+q)-Math.sqrt(0.25*(p+q)*(p+q)-p*q+gam*gam);
			Lam.add(new Double(lambda));
			pw.println(Kx+" "+Ky+" "+lambda+" "+Math.sqrt(lambda));
			if(Math.abs(lambda)<0.00000000001)
			    System.out.println(Kx+" "+Ky+" "+lambda);

			if(0.25*(p+q)*(p+q)-p*q+gam*gam==0)
			    System.out.println("!!"+Kx+" "+Ky+" "+lambda);
		    }

		phi=N*Math.PI*Rad*Rad/(Lengx*Lengy);
		System.out.println("PHI: "+phi);
		Collections.sort(Lam);//昇順
		//Collections.reverse(Lam);//降順
		pw.println("\n--------------------------");

		prlamtmp=prlam=Lam.get(0);
		pw.println("* "+prlam);
		pw2.println(prlam+" "+Math.sqrt(prlam)+" "+cum+" "+0.0);
		for(int i=0;i<2*sqrtN;i++)
		    for(int j=0;j<sqrtN;j++) {
			if(i==0 && j==0)
			    ;//*を打つために(i,j)=(0,0)を分離
			else {
			    prlam=Lam.get(sqrtN*i+j);
			    if(Math.abs(prlam-prlamtmp)>0.000000001) {
				pw.print("* ");
			    }
			    prlamtmp=prlam;
			    cum-=dcum;
			    pw.println(prlam);
			    if(Math.abs(prlam)>0.0000000001) {
				pw2.println(prlam+" "+Math.sqrt(prlam)+" "+cum+" "+0.0);
			    }
			    else {
				pw2.println(prlam+" "+Math.sqrt(prlam)+" "+0.0+" "+0.0);
			    }
			}
		    }
		pw.close();
		pw2.close();
	    }
	    
	    else
		System.out.println("Cannot write your file><");
	}
	
	catch(IOException e) {
	    System.out.println(e);
	}
    }

    private static boolean checkBeforeWritefile(File file)
    {
	if(file.exists()) {
	    if(file.isFile() && file.canWrite()) {
		return true;
	    }
	}
	return false;
    }
}
