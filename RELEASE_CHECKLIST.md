# Release Checklist

- [ ] Confirm the working tree contains only intended source and documentation.
- [ ] Confirm generated files, runtime state, personal data, and credentials are excluded.
- [ ] Run every build, test, lint, and formatting command documented for the project.
- [ ] Review dependencies and address high-severity advisories.
- [ ] Verify README instructions from a clean checkout.
- [ ] Confirm `CITATION.cff`, license, changelog, and version agree.
- [ ] Review third-party assets and their redistribution permissions.
- [ ] Create a signed or annotated Semantic Versioning tag.
- [ ] Create the GitHub Release and verify its generated source archives.
- [ ] If Zenodo is enabled, verify the DOI record, creators, ORCID, license, and files before publication.

A GitHub or Zenodo release must not be created while any applicable item remains incomplete.
