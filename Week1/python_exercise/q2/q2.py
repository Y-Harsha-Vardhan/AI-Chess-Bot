import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def PCA(init_array: pd.DataFrame):

    sorted_eigenvalues = None
    final_data = None
    dimensions = 2

    # TODO: transform init_array to final_data using PCA
    
    init_array = init_array - np.mean(init_array,axis=0)
    

    cov_matrix = np.cov(init_array.transpose())
    
    eigenvalues,eigenvectors = np.linalg.eigh(cov_matrix)
    

    temp = sorted(map(list,list(zip(eigenvalues,eigenvectors.transpose()))))
    sorted_eigenvalues,sorted_eigenvectors = list(zip(*temp))
    
    dim_eigenvectors = np.array(list(map(list,sorted_eigenvectors[-1:-1-dimensions:-1])))
   
    # Transform the data to the new subspace
    final_data = np.matmul(init_array, dim_eigenvectors.transpose())
    
    # END TODO

    return sorted_eigenvalues, final_data


if __name__ == '__main__':
    init_array = pd.read_csv("pca_data.csv", header = None)
    sorted_eigenvalues, final_data = PCA(init_array)
    
    np.savetxt("transform.csv", final_data, delimiter = ',')
    for eig in sorted_eigenvalues:
        print(eig)

    # total_variance = np.sum(sorted_eigenvalues)
    # explained_variances = [(i / total_variance) * 100 for i in sorted_eigenvalues]
    # print(explained_variances)
    

    # TODO: plot scatter plot of final_data 
    plt.scatter(final_data[0],final_data[1])
    plt.xlim(-15,15)
    plt.ylim(-15,15)
    plt.show()
    # END TODO
    
