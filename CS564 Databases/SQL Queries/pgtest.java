import java.sql.DriverManager;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Types;
import java.util.Properties;
import java.util.Random;
import java.util.Scanner;

public class pgtest{

	/**

	 * @param args

	 * @throws Exception

	 */

	public static void main(String[] args) throws Exception {

		String url = "jdbc:postgresql://stampy.cs.wisc.edu/cs564instr?sslfactory=org.postgresql.ssl.NonValidatingFactory&ssl";

		Connection conn = DriverManager.getConnection(url);

		Statement st = conn.createStatement();


		// Set up needed variables
		long seed = System.currentTimeMillis() % 1000;
		Scanner in = new Scanner(System.in);
		Random rand = new Random(seed);
		boolean keepGoing = true;
		boolean print = true;
		boolean table = false;
		ResultSet rs = null;
		String tableName = "";
		// Begin program loop
		while (keepGoing) {
			print = true;
			table = false;
			String command;

			// Display repeated main prompt and receive command
			System.out.println("Enter a command:\n"
					+ "q : For Query Sampling\n"
					+ "t : For Table Sampling\n"
					+ "r : For Seed Reset\n"
					+ "e : To Exit");

			command = in.nextLine();
			// Switch on the command
			switch (command) {
			// Table and query will do nearly the same thing
			case "t" :	table = true;
			case "q" :
				String tempTable = "tttemporaryyy" + rand.nextInt(1000);
				String query;
				//String queryFull;

				// Prompt and receive query/table info
				if (!table){
					System.out.println("Please enter your desired Query: ");
				}
				else {
					System.out.println("Please enter your desired Table: ");
				}
				query = in.nextLine();

				// Prompt and receive number of rows to sample
				System.out.println("Please enter your desired number of sampled rows: ");
				int n = in.nextInt();
				in.nextLine();

				//queryFull = "select * from (select *, row_number() over() from(" + query + ") as p6k3) as z4x1 where z4x1.row_number = ";
				// Prompt user if they want to create a table or merely see the output
				System.out.println("Would you like a table created?(y/n): ");
				String yn = in.nextLine();
				// Set up info for user printing or tabling
				if (yn.equals("y")) {
					System.out.println("Please enter your desired table name: ");
					tableName = in.nextLine();
					print = false;
				}
				else if (yn.equals("n")) {
					print = true;
				}
				else {
					break;
				}

				// Create temporary views from table or query
				if (table) {
					st.executeUpdate("create view " + tempTable + " as select *, row_number() over() from " + query);
				}
				else {
					st.executeUpdate("create view " + tempTable + " as select *, row_number() over() from(" + query + ") as p6k3");
				}

				// Get the size of resulting table
				rs = st.executeQuery("select count(*) from " + tempTable);
				rs.next();
				double N = rs.getInt(1);
				// If this size is smaller than requested samples, simply display all rows
				if (n>N) {
					System.out.println("Number of samples requested was greater than the number of entries in the given table/query, thus all entries are returned.");
					if(!print) {
						st.executeUpdate("create table " + tableName + " as " + "select * from " + tempTable);
						System.out.println("Samples redirected to table " + tableName +".");
					}
					//
					else {
						rs = st.executeQuery("select * from " + tempTable);
						ResultSetMetaData rsmd= rs.getMetaData();
						while (rs.next()) {
							int colType = 0;
							int numCol = 0;
							numCol = rsmd.getColumnCount();
							for (int i = 1; i <= numCol; i++){
								colType = rsmd.getColumnType(i);
								switch(colType) {
								case Types.INTEGER:
									System.out.print(rs.getInt(i));
									break;
								case Types.VARCHAR:
									System.out.print(rs.getString(i));
									break;
								case Types.REAL:
									System.out.print(rs.getDouble(i));
									break;
								case Types.BOOLEAN:
									System.out.print(rs.getBoolean(i));
									break;
								case Types.BIT:
									System.out.print(rs.getBoolean(i));
									break;
								case Types.CHAR:
									System.out.print(rs.getString(i));
									break;
								case Types.DATE:
									System.out.print(rs.getDate(i));
									break;
								case Types.BIGINT:
									System.out.print(rs.getLong(i));
									break;
								case Types.SMALLINT:
									System.out.print(rs.getInt(i));
									break;
								default:
									System.out.print(colType + ": ");
									System.out.print("Error, column type could not be identified.");
									break;
								}
								if(i != numCol){
									System.out.print(",");
								}
							}
							System.out.println();
						}
					}
					st.executeUpdate("drop view " + tempTable);
					break;	
				}

				// Only get here if samples requested is less than total samples
				// Perform knuth's algorithm
				double t = 0;
				double m = 0;
				double u = 0;
				while(m < n) {
					u = rand.nextDouble();
					if(((N-t)*(u))>=(n-m)) {
						t++;
						continue;
					}

					if(!print) {
						if (m==0){
							st.executeUpdate("create table " + tableName + " as " + "select * from " + tempTable + " where row_number = " + t);
						}
						else {
							st.executeUpdate("insert into " + tableName + " select * from " + tempTable + " where row_number = " + t);
						}
					}
					else {
						rs = st.executeQuery("select * from " + tempTable + " where row_number = " + t);
						ResultSetMetaData rsmd= rs.getMetaData();
						while (rs.next()) {
							int colType = 0;
							int numCol = 0;
							numCol = rsmd.getColumnCount();
							for (int i = 1; i <= numCol; i++){
								colType = rsmd.getColumnType(i);
								switch(colType) {
								case Types.INTEGER:
									System.out.print(rs.getInt(i));
									break;
								case Types.VARCHAR:
									System.out.print(rs.getString(i));
									break;
								case Types.REAL:
									System.out.print(rs.getDouble(i));
									break;
								case Types.BOOLEAN:
									System.out.print(rs.getBoolean(i));
									break;
								case Types.BIT:
									System.out.print(rs.getBoolean(i));
									break;
								case Types.CHAR:
									System.out.print(rs.getString(i));
									break;
								case Types.DATE:
									System.out.print(rs.getDate(i));
									break;
								case Types.BIGINT:
									System.out.print(rs.getLong(i));
									break;
								case Types.SMALLINT:
									System.out.print(rs.getInt(i));
									break;
								default:
									System.out.print(colType + ": ");
									System.out.print("Error, column type could not be identified.");
									break;
								}
								if(i != numCol){
									System.out.print(",");
								}
							}
							System.out.println();
						}
					}
					m++;
					t++;

					if (m >= N) {
						if (!print) {
							System.out.println("Samples redirected to table " + tableName +".");
						}
						System.out.println("Number of samples requested,"+n+", was greater that the number of samples in the desired query/table," +N+".");
						break;
					}
					if (t > N) {
						if (!print) {
							System.out.println("Samples redirected to table " + tableName +".");
						}
						System.out.println("Number of samples requested,"+n+", was greater that the number of samples able to be returned from the query/table," +N+".");
						break;
					}
				}

				// Drop the temporary view
				st.executeUpdate("drop view " + tempTable);
				if (!print) {
					System.out.println("Samples redirected to table " + tableName +".");
				}
				break;
			// Reset seed if commanded to
			case "r" :
				seed = System.currentTimeMillis() % 100000;
				rand = new Random(seed);
				System.out.println("Random seed reset to " + seed);
				break;
			// Exit if commanded to
			case "e" :
				System.out.println("Exiting...");
				keepGoing = false;
				break;
			// Display error if command invalid
			default:
				System.out.println("Invalid Command!");
				break;
			}
		}
		// close up shop

		if (rs != null){
			rs.close();
		}

		st.close();

		conn.close();

	}

}
