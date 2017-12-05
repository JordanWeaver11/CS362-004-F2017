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
	   System.out.println("MANUAL TEST:");
	   
	   //Valid URLS
	   System.out.println("Testing VALID URLS (all return true):");
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
			   //assertTrue(strLine, urlVal.isValid(strLine));
			   System.out.println(" " + urlVal.isValid(strLine) + " " + strLine);
		   }
		   //close the file
		   //fstream.close();
	   }catch (Exception e) {  //error handling
		   System.err.println("Error: " + e.getMessage());
	   }
	   
	   //Invalid URLS
	   System.out.println("Testing INVALID URLs (all return false):");
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
			   //assertFalse(strLine, urlVal.isValid(strLine));
			   System.out.println(" " + urlVal.isValid(strLine) + " " + strLine);
		   }
		   //close the file
		   //fstream.close();
	   }catch (Exception e) {  //error handling
		   System.err.println("Error: " + e.getMessage());
	   }
	   
	   
	   /*
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   //True
	   assertTrue(urlVal.isValid("https://www.google.com"));
	   assertTrue(urlVal.isValid("http://www.google.com"));
	   assertTrue(urlVal.isValid("http://flob.com"));
	   assertTrue(urlVal.isValid("http://255.255.255.255"));
	   assertTrue(urlVal.isValid("http://google.au"));
	   assertTrue(urlVal.isValid("www.google.com"));
	   assertTrue(urlVal.isValid("www.google.com:80"));
	   assertTrue(urlVal.isValid("www.google.com:65535"));
	   assertTrue(urlVal.isValid("www.randomness.com"));
	   assertTrue(urlVal.isValid("http://www.google.com/file/test"));
	   assertTrue(urlVal.isValid("http://www.google.com/file/test/"));
	   assertTrue(urlVal.isValid("http://www.google.com/file/test/?action=view"));
	   assertTrue(urlVal.isValid("http://www.google.com/file/test?action=view"));
	   //False
	   assertFalse(urlVal.isValid("xyz://www.google.com"));
	   assertFalse(urlVal.isValid("ftp://www.google.com"));
	   assertFalse(urlVal.isValid("http:www.google.com"));
	   assertFalse(urlVal.isValid("http:/www.google.com"));
	   assertFalse(urlVal.isValid("1.1.1.1."));
	   assertFalse(urlVal.isValid("1.1.1."));
	   assertFalse(urlVal.isValid("1.1."));
	   assertFalse(urlVal.isValid("1."));
	   assertFalse(urlVal.isValid("1.1.1"));
	   assertFalse(urlVal.isValid(".google.com"));
	   assertFalse(urlVal.isValid("http://www.google.com:-1"));
	   assertFalse(urlVal.isValid("http://www.google.com:80x"));
	   assertFalse(urlVal.isValid("http://www.google.com:"));
	   assertFalse(urlVal.isValid("www.google.com/test/%fail"));
	   assertFalse(urlVal.isValid("www.google.com/.../"));
	   assertFalse(urlVal.isValid("www.google.com?action=view"));
	   assertFalse(urlVal.isValid(":80www.google.com"));
	   assertFalse(urlVal.isValid("www.google.comhttps://"));
	   assertFalse(urlVal.isValid("https://test/file/www.google.com"));
	   assertFalse(urlVal.isValid("://www.google.com"));
	   */
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
