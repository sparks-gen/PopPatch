<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a id="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]
-->


<!-- PROJECT LOGO 
<br />
<div align="center">
  <a href="https://github.com/sparks-gen/PopPatch">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>
  -->

<h3 align="center">PopPatch</h3>

  <p align="center">
    Replace sequences within an existing reference genome to better represent 
    your target population or even species.
    <br />
    <a href="https://github.com/sparks-gen/PopPatch"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/sparks-gen/PopPatch/issues/new?assignees=&labels=&projects=&template=bug_report.md&title=">Report Bug</a>
    ·
    <a href="https://github.com/sparks-gen/PopPatch/issues/new?assignees=&labels=&projects=&template=feature_request.md&title=">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project



<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

<a href="https://www.cprogramming.com/"><img src="https://github.com/bablubambal/All_logo_and_pictures/blob/main/programming%20languages/c.svg" alt="C Programming Logo" style="width:100px;height:100px;"></a>

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

To get PopPatch up and running follow these simple example steps.

### Prerequisites

* A shell terminal
* A reference genome
* An alignment file (SAM) created by aligning an assembly to your reference 
genome of choice.

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/sparks-gen/PopPatch.git
   ```
2. Compile by running
   ```sh
   make
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

Once the program has been compiled, simply provide it the alignment file and the
reference genome. Optionally, you can provide a prefix to represent what would 
you would like the output to be called.
```sh
./poppatch -f coat -m alignment.sam -r GRCh38.fna -p newReference
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

- [ ] Feature 1
- [ ] Feature 2
- [ ] Feature 3
    - [ ] Nested Feature

See the [open issues](https://github.com/sparks-gen/PopPatch/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Top contributors:

<a href="https://github.com/sparks-gen/PopPatch/graphs/contributors">
  sparks-gen
</a>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Your Name - [@twitter_handle](https://twitter.com/twitter_handle) - email@email_client.com

Project Link: [https://github.com/sparks-gen/PopPatch](https://github.com/sparks-gen/PopPatch)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* []()
* []()
* []()

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/sparks-gen/PopPatch.svg?style=for-the-badge
[contributors-url]: https://github.com/sparks-gen/PopPatch/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/sparks-gen/PopPatch.svg?style=for-the-badge
[forks-url]: https://github.com/sparks-gen/PopPatch/network/members
[stars-shield]: https://img.shields.io/github/stars/sparks-gen/PopPatch.svg?style=for-the-badge
[stars-url]: https://github.com/sparks-gen/PopPatch/stargazers
[issues-shield]: https://img.shields.io/github/issues/sparks-gen/PopPatch.svg?style=for-the-badge
[issues-url]: https://github.com/sparks-gen/PopPatch/issues
[license-shield]: https://img.shields.io/github/license/sparks-gen/PopPatch.svg?style=for-the-badge
[license-url]: https://github.com/sparks-gen/PopPatch/blob/master/LICENSE.txt
<!-- [linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/linkedin_username -->
[C.com]: https://www.cprogramming.com/
[C-url]: https://www.cprogramming.com/
