import java.util.Arrays;

/**
 * A k-means clustering algorithm implementation.
 * 
 */

public class KMeans {
	public KMeansResult cluster(double[][] centroids, double[][] instances, double threshold) {
		//create new result
		KMeansResult result = new KMeansResult();
		//current centorids
		double[][] currCentroids = centroids;
		//distortions at different iterations
		double[] distortions = new double[1];
		//stop boolean
		boolean stop = false;
		//iteration count
		int iteration = 0;
		//assignment of clusters for each instance
		int[] clusterAssignment = new int[instances.length];
		//until stop is reached
		while(stop == false)
		{
			//new cluster
			double[][] newCentroids = new double[currCentroids.length][currCentroids[0].length];
			//assign clusters
			int[] clusterCount = new int[currCentroids.length];
			int farCluster = 0;
			double farClusterDistance = 0;
			//go through instances
			for (int instance = 0; instance < instances.length; instance++)
			{
				//distance to closest cluster
				double distance = Double.MAX_VALUE;
				//go though clusters
				for (int cluster = 0; cluster < currCentroids.length; cluster++)
				{
					//distance to current cluster
					double instanceDistance = 0;
					//go though features
					for (int feature = 0; feature < instances[0].length; feature++)
					{
						//calculate euclidean distance
						instanceDistance += Math.pow(currCentroids[cluster][feature]-instances[instance][feature], 2);
					}
					instanceDistance = Math.sqrt(instanceDistance);
					//if the distance to this cluster is less than the distance to the previous closest cluster, assign it to be the new closest cluster
					if(instanceDistance<distance)
					{
						distance = instanceDistance;
						clusterAssignment[instance]=cluster;
					}
					//if the distance to this cluster is more than the farthest instance, assign it to the farthest instance
					if (instanceDistance>farClusterDistance)
					{
						farClusterDistance = instanceDistance;
						farCluster = instance;
					}
				}
				//go through the features
				for (int feature = 0; feature < instances[0].length; feature++)
				{
					//add the value of the current instance to the position of its assigned centroid
					newCentroids[clusterAssignment[instance]][feature]+=instances[instance][feature];
				}
				//increment the count of instances in the cluster
				clusterCount[clusterAssignment[instance]]++;
			}
			//go through the clusters
			for (int cluster = 0; cluster < newCentroids.length; cluster++)
			{
				//go though features
				for (int feature = 0; feature < newCentroids[0].length; feature++)
				{
					//reassign orphaned clusters
					if (clusterCount[cluster]==0)
					{
						newCentroids[cluster]=instances[farCluster];
						feature = centroids[0].length;
					}
					else
					{
						//get the new centroid position
						newCentroids[cluster][feature]=newCentroids[cluster][feature]/(clusterCount[cluster]);
					}
				}
			}
			//distortion for this itertion
			double currDistortion = 0;
			//go through instances
			for (int instance = 0; instance < instances.length; instance++)
			{
				//go through features
				for (int feature = 0; feature < instances[instance].length; feature++)
				{
					//calculate distortion
					currDistortion += Math.pow((instances[instance][feature]-newCentroids[clusterAssignment[instance]][feature]), 2);
				}
			}
			//dynamically allocate the length of the distortions array
			if (iteration >= distortions.length)
			{
				distortions = Arrays.copyOf(distortions, distortions.length+1);
			}
			//set the distortion for this iteration to currDistortion
			distortions[iteration] = currDistortion;
			//set the currCentroids to the new centroids
			currCentroids = newCentroids;
			if (iteration>0)
				//if the distortion difference exceeds the threshold, stop the k means
				if (Math.abs((distortions[iteration]-distortions[iteration-1])/distortions[iteration-1])<threshold)
					stop = true;
			//increment iteration
			iteration++;
		}
		//set the contentes of result to the data collected and return the result
		result.centroids = currCentroids;
		result.distortionIterations=distortions;
		result.clusterAssignment=clusterAssignment;
		return result;
	}
}
