### Software Testing

As a software developer, it is important to ensure correct functionality and security in your program. Manual review and automated testing must be effectively integrated at the unit, integration, and end-to-end system levels. This includes static (non-executing) and dynamic (executing) testing, as well as regression testing to ensure updates do not break previously working code. Automated testing can be implemented to support frequent software updates/releases, as part of a Continuous Integration/Continuous Deployment (CI/CD) framework.

The following resources can be referenced for security-related vulnerabilities and mitigation strategies:
* OWASP (Open Web Application Security Project)
* NIST (National Institute of Standards & Technology)
* CERT (Computer Emergency Response Team)
* ISO/IEC
(Intl. Organization for Standardization/Intl. Electrotechnical Commission)
* Oracle
* CWE (Common Weakness Enumeration)
* CVE (Common Vulnerabilities & Exposures)

A few of the U.S. governmental compliancy regulations and laws for data integrity and security are composed of the following:
* SOX (Sarbanes-Oxley Act)
* FISMA (Federal Information Security Management Act)
* HIPAA (Health Insurance Portability & Accountability Act)
* FISMA (Federal Information Security Management Act)

Proper security requires different methods to be used in conjunction with each other. Some common strategies include the following:
* input validation/sanitization
* session management
* authentication and authorization (access control)
* secure communication and proper key management
* PoLP/PoLA (Principle of Least Privilege/Authority)
* parameterized queries
•	HTTPS and TLS (SSL)
* proper RSA/AES encryption
* proper SHA hashing
* proper error handling
* updated framework, plugins, dependencies, libraries, APIs 

Following the guidelines set forth by the aforementioned resources provides the foundation for functional and secure software development. A Test-Driven Approach (TDD) is often used in many iterative software development approaches, as seen in agile frameworks like Scrum, and is proven to be quite effective for developing robust software.

ISO/IEC 12207 can be used when implementing the Software Development Lifecycle (SDLC), which typically starts off with Planning and Requirements Elicitation. It is critical to understand the user needs, in terms of functional requirements and non-functional requirements (operational, performance, scalability, security, etc.). This phase focuses on defining high-level requirements collected from various stakeholders/users. Some of the techniques that can be used for this process include the following:
* interviews
* questionnaires
* direct observation
* document analysis
* Joint Application Development (JAD) sessions
* prototyping
* user testing
* clear documentation

Before moving onto the Analysis phase, the requirements should be well understood. However, user stories and UML (Unified Modeling Language) use-case diagrams can be created and used to produce UML class diagrams to better refine the software requirements for the Analysis phase. Usability testing, User Acceptance Testing, and beta testing can also be used to verify and validate user requirements have been satisfied.

Designing software typically starts by creating a Requirements Definition Document (RDD) to define at a high-level what the system should do. This is determined by requirements gathered during interviews, JAD sessions, questionnaires, and other techniques previously mentioned. Then a Project Charter can be created to present high-level objectives/timeline, project scope, risk assessment, budget, success criteria, and a list of stakeholders. A Baseline Project Plan can detail the schedule and dependencies, resources, cost/budget, quality standards/metrics, risk management plan, and performance measurement criteria. Then design of documentation such as UML Use-Case Diagrams, Activity Diagrams, and Sequence Diagrams may be created. 

Finally, the logical and physical (architectural) design can be created and may include structural diagrams (Component, Deployment, Object, Package, Profile Diagrams), behavioral diagrams (Communication, State Diagrams), and functional models (Use-Case Descriptions/Diagrams, Data Flow Diagrams). Presentation of this information can be shown via a Design Document Specification (DDS), Business Requirements Document (BRD), Software Requirements Specification (SRS), System Design Document (SDD), or Functional Specification Document (FSD).


As part of a Test-Driven Approach (TDD), a Master Test Plan can be created to include verification consisting of the Unit Test Plan, Integration Test Plan, and System Test Plan. Acceptance testing can be done after passing system tests and includes testing in the environment(s) the software will actually be used in with the aim of being accepted by its end-users (validation). Ongoing testing and development should be expected in order to keep up with changing user needs and newly-discovered security vulnerabilities and other modernization requirements. Dev on!
