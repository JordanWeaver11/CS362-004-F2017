/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;
import java.io.*;



/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   //Valid URLS
	   System.out.println("Testing Valid URLS:");
	   //error handling
	   try {
		   //open the file
		   InputStream input = this.getClass().getResourceAsStream("ValidURLS.txt");
		   InputStreamReader fstream = new InputStreamReader(input, "UTF-8");
		   BufferedReader br = new BufferedReader(fstream);
		   String strLine = null;
		   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		   //read a line from the file into strLine
		   while ((strLine = br.readLine()) != null) {
			   //test each line from the file
			   assertTrue(urlVal.isValid(strLine));
			   //System.out.println(urlVal.isValid(strLine));
		   }
		   //close the file
		   //fstream.close();
	   }catch (Exception e) {  //error handling
		   System.err.println("Error: " + e.getMessage());
	   }
	   
	   //Invalid URLS
	   System.out.println("Testing Invalid URLS:");
	   //error handling
	   try {
		   //open the file
		   InputStream input = this.getClass().getResourceAsStream("InValidURLS.txt");
		   InputStreamReader fstream = new InputStreamReader(input, "UTF-8");
		   BufferedReader br = new BufferedReader(fstream);
		   String strLine = null;
		   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		   //read a line from the file into strLine
		   while ((strLine = br.readLine()) != null) {
			   //test each line from the file
			   assertFalse(urlVal.isValid(strLine));
			   //System.out.println(urlVal.isValid(strLine));
		   }
		   //close the file
		   //fstream.close();
	   }catch (Exception e) {  //error handling
		   System.err.println("Error: " + e.getMessage());
	   }
	   
   }
   
   
   public void testYourFirstPartition()
   {
	   
   }
   
   public void testYourSecondPartition(){
	   
   }
   
   
   public void testIsValid()
   {
	   for(int i = 0;i<10000;i++)
	   {
		   
	   }
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
