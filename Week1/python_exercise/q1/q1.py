import json
import numpy as np
import matplotlib.pyplot as plt

def inv_transform(distribution: str, num_samples: int, **kwargs) -> list:
    """ populate the 'samples' list from the desired distribution """

    samples = []
    
    # TODO: first generate random numbers from the uniform distribution

    vals = np.random.random_sample((num_samples,))
    
    if (distribution == "exponential"):
        # F(x) = 1 - e^(-lambda x)
        # x = -ln(1 - F(x))/lambda
        samples = np.emath.log(1-vals)/-kwargs["lambda"]
        

            
    else:
        # F(x) = 1/pi * (arctan(x-peak_x)/gamma) + 0.5 
        samples = np.tan((vals-0.5)*np.pi)*kwargs["gamma"]+kwargs["peak_x"]
    return list(samples)
    # END TODO



if __name__ == "__main__":
    np.random.seed(42)

    for distribution in ["cauchy","exponential"]:
        file_name = "q1_" + distribution + ".json"
        args = json.load(open(file_name, "r"))
        samples = inv_transform(**args)
        # TODO: plot and save the histogram to "q1_" + distribution + ".png"
        with open("q1_output_" + distribution + ".json", "w") as file:
            json.dump(samples, file)
        if distribution == "exponential":
            plt.hist(samples,bins=100,range=(0,4))
        else:
            plt.hist(samples,bins=100,range=(-60,40))
       
        plt.savefig(f"q1_{distribution}.png")
        plt.show()
        # END TODO
    
